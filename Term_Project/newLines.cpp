#include "newLines.h"

/*
 * initializeVector() - 파일 시스템에서 라인을 읽어와 벡터에 단어 단위로 삽입하고 커서의 위치를 정의한다.
 */
void Console::initializeVector() {
	string word;
	ifstream file("test.txt");

	if (file.is_open()) {
		while (file) {
			while (getline(file, word, ' ')) { //file에서 공백을 기준으로 단어를 읽어온다.
				newLines.push_back(word); //읽어온 단어를 모두 벡터에 push 한다.
			}
		}
		file.close(); // 파일 닫기
		current_cursor = 0; //커서 초기화
	}
	else cout << "콘솔에서 작업할 파일을 불러오는데 실패하였습니다." << endl;
}

/*
 * printConsole() - 현재 벡터의 값을 기준으로 콘솔창을 출력한다.
 */
void Console::printConsole(string consoleMessage) {
	system("cls"); //지금까지의 출력을 지우고 새롭게 콘솔창을 출력한다.

	/* 텍스트 출력 시작 */

	string line; //완성된 문장을 저장하는 임시 변수. 출력이 끝나면 다음 문장을 담는다.
	int byteCount = 0, lineCount = 1; //line(20)과 byte(75)의 수를 결정하기 위해 사용하는 count 변수.
	vector<string>::iterator itr = newLines.begin(); //newLines 접근을 위한 반복자

	//현재 cursor가 갖는 index만큼 반복자를 이동시킨다.
	for (int c = current_cursor; c > 0; c--) {
		itr++;
	}
	next_cursor = current_cursor;

	//현재 반복자 itr의 위치부터 20lines를 콘솔에 출력한다.
	for (; itr != newLines.end(); itr++) {
		if (lineCount <= 20) { //lineCount는 20을 넘을 수 없다.

			byteCount += itr->length(); //byteCount에 현재 word의 길이를 저장한다.

			if (byteCount <= 75) { //byteCount는 75를 넘을 수 없다.
				line += *itr; //line에 현재 단어를 추가한다.
				line += ' '; //단어 사이에 공백 추가

				byteCount += 1; //byteCount에 공백을 추가해서 계산
			}
			else { //byteCount가 75를 넘어 line이 완성됨
				//완성된 라인 출력
				cout << setw(2) << lineCount << "| " << line << endl;

				//라인 초기화
				line.clear();
				line.resize(0);

				//Count 변수 조정
				lineCount += 1;
				byteCount = 0;

				//새로운 line에 현재 word추가
				line += *itr;
				line += ' ';
				//새로운 byteCount에 현재 word의 길이 추가
				byteCount += itr->length() + 1;
			}
		}
		else break; // lineCount가 20이 되면 종료
		next_cursor++;
	}
	next_cursor--;
	//20라인이 초과되지 않는 상태에서 마지막 라인은 75byte가 되지 못하면 출력되지 않는다. 이를 보정
	if (byteCount != 75 && itr == newLines.end()) {
		cout << setw(2) << (lineCount == 0 ? 1 : lineCount) << "| " << line << endl;
	}

	/* 텍스트 출력 완료 */

	printConsole_line();

	cout << "n:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후종료" << endl;

	printConsole_line();

	cout << consoleMessage << endl; //매개변수로 전달받은 콘솔 메시지를 출력

	printConsole_line();

	cout << "입력 : " << endl;

	printConsole_line();

	//명령어 입력을 위해 커서의 위치를 '입력: ' 다음으로 조정
	COORD pos;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

	pos.X = 7;
	pos.Y = curInfo.dwCursorPosition.Y - 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*
 * printConsole_line() - printConsole()에서 사용하는 함수, 구역 구분용 선을 출력
 */
void Console::printConsole_line() {
	string acrossLine;

	for (int c = 0; c < 83; c++) {
		acrossLine += '-';
	}

	cout << acrossLine << endl;
}

/*
 * nextInput() - 다음 명령을 입력받고 해석한다.
 *				해석한 명령대로 함수를 실행하고 완료된 함수에서 보내는 메시지를 main()함수로 전달한다.
 */
string Console::nextInput() {
	string input; //입력받는 명령어 저장
	vector<string> inputSplit; //입력받은 명령어를 구분해서 벡터에 저장, checkError에서 생성한다.

	getline(cin, input); //공백을 포함한 문자열을 \n까지 입력받는다.

	/* 명령어 오류 체크 */

	try {
		//명령어에 오류가 없으면 명령어를 분리해서 벡터에 저장한 것을 리턴한다.
		inputSplit = checkError(input);
	}
	catch (string& e) {
		//오류가 있을 경우 해당 오류 메시지를 담은 string을 main() 으로 리턴한다.
		return e;
	}

	/* 명령어 실행 */

	try { //명령어를 실행하고 해당 명령어에서 리턴하는 메시지를 main()으로 전달한다.
		switch (input[0]) {
		case 'i':
			return i_insertWord(inputSplit);
			break;
		case 'd':
			return d_deleteWord(inputSplit);
			break;
		case 's':
			return s_realign(inputSplit);
			break;
		case 'c':
			return c_changeWord(inputSplit);
			break;
		case 't':
			return t_saveAndExit();
			break;
		case 'n':
			return n_nextPage();
			break;
		case 'p':
			return p_previousPage(false);
			break;
		default:
			//checkError에서 허용되지 않는 명령어를 체크하므로 다시 체크할 필요 없다.
			break;
		}
	}
	catch (string& e) { //명령어 실행 함수에서 오류가 발생한 경우 작동을 멈추고 해당 오류 메시지를 main()으로 전달한다.
		return e;
	}
	catch (int& e) { //t_saveAndExit()에서 콘솔을 종료하기 위한 flow
		return "exit";
	}

}

/*
 * checkError() - 입력된 명령어의 오류 여부를 체크하고 명령어를 split한 inputSplit을 제공한다.
 *				 오류가 발견되면 nextInput() 함수로 예외를 throw한다.
 */
vector<string> Console::checkError(string input) {

	vector<string> inputSplit;

	//가장 먼저 명령어에 공백이 있으면 오류 처리
	if (input.find(" ") != string::npos) {
		throw string("명령어가 올바르지 않습니다. - 명령어에 공백이 존재합니다!");
	}
	if (input.length() == 0) {
		throw string("명령어가 올바르지 않습니다. - 명령어를 입력해주세요!");
	}

	/*
	 * 명령어 별 오류 체크
	 */

	 //1. t, n, p 명령어는 인자가 없으므로 명령어뒤에 불필요한 문자가 있는지만 검사한다.
	if (input[0] == 't' || input[0] == 'n' || input[0] == 'p') {
		if (input.length() != 1) {
			throw string("명령어가 올바르지 않습니다. - 불필요한 인자가 존재합니다!");
		}
		else {
			//정상적인 경우 inputSplit에 문자를 추가하고 nextInput()으로 리턴한다.
			inputSplit.push_back(input);
			return inputSplit;
		}
	}

	//2. i, d, s, c 명령어는 인자가 존재하므로 명령어를 분리해서 검사한다.

	//2-1. 먼저 괄호를 제대로 입력했는지 검사하고 올바르다면 괄호를 삭제한다.
	if (!(input.substr(1, 1) == "(" && *(input.end() - 1) == ')')) {
		throw string("명령어가 올바르지 않습니다. - '명령어(인자)'의 형식을 지켜주세요!");
	}
	else {
		//괄호를 지운다.
		input.erase(1, 1);
		input.pop_back();
	}

	//2-2. 명령어의 인자 개수가 올바른지 확인하고 명령어를 벡터 inputSplit으로 분리한다.
	checkNumOfParameterAndSplitInput(input, inputSplit);

	//2-3. 벡터에 저장된 인자를 바탕으로 정확한 명령어가 입력되었는지 확인한다.
	if (inputSplit[0] == "i") {

		//첫번째, 두번째 인자에 정수가 아닌 문자가 입력되면 에러
		if (!is_integer(inputSplit[1]) || !is_integer(inputSplit[2])) {
			throw string("명령어가 올바르지 않습니다. - i 명령어의 1,2번 인자는 정수여야 합니다!");
		}
		//line을 의미하는 첫 번째 인자가 0이하거나 20초과이면 에러
		if ((stringToInt(inputSplit[1]) <= 0) || (stringToInt(inputSplit[1]) > 20)) {
			throw string("명령어가 올바르지 않습니다. - i 명령어의 1번 인자는 1과 20 사이의 수여야 합니다!");
		}
		//word를 의미하는 두 번째 인자가 0이하면 에러
		if ((stringToInt(inputSplit[2]) < 0)) {
			throw string("명령어가 올바르지 않습니다. - i 명령어의 2번 인자는 0이상이어야 합니다!");
		}
		//변경할 문자열을 의미하는 세 번째 인자는 75바이트를 초과할 수 없다.
		if (inputSplit[3].length() > 75) {
			throw string("명령어가 올바르지 않습니다. - i 명령어의 3번 인자는 75바이트를 초과할 수 없습니다!");
		}

		//오류가 없으면 벡터를 리턴한다.
		return inputSplit;
	}
	else if (inputSplit[0] == "d") {

		//첫번째, 두번째 인자에 정수가 아닌 문자가 입력되면 에러
		if (!is_integer(inputSplit[1]) || !is_integer(inputSplit[2])) {
			throw string("명령어가 올바르지 않습니다. - d 명령어의 각 인자는 정수여야 합니다!");
		}
		//line을 의미하는 첫 번째 인자가 0이하거나 20초과이면 에러
		if ((stringToInt(inputSplit[1]) <= 0) || (stringToInt(inputSplit[1]) > 20)) {
			throw string("명령어가 올바르지 않습니다. - d 명령어의 1번 인자는 1과 20 사이의 수여야 합니다!");
		}
		//word를 의미하는 두 번째 인자가 0이하면 에러
		if ((stringToInt(inputSplit[2]) <= 0)) {
			throw string("명령어가 올바르지 않습니다. - d 명령어의 2번 인자는 1이상이어야 합니다!");
		}

		//오류가 없으면 벡터를 리턴한다.
		return inputSplit;
	}
	else if (inputSplit[0] == "s") {

		if ((inputSplit[1].length() > 75)) {
			throw string("명령어가 올바르지 않습니다. - s 명령어의 인자는 75바이트를 초과할 수 없습니다!");
		}

		//오류가 없으면 벡터를 리턴한다.
		return inputSplit;
	}
	else if (inputSplit[0] == "c") {

		//각 인자가 75byte를 초과하면 에러
		if ((inputSplit[1].length() > 75) || (inputSplit[2].length() > 75)) {
			throw string("명령어가 올바르지 않습니다. - c 명령어의 각 인자는 75바이트를 초과할 수 없습니다!");
		}
		//오류가 없으면 벡터를 리턴한다.
		return inputSplit;
	}
	else { //명령어의 첫 문자가 지정되지 않은 문자일 경우
		throw string("명령어가 올바르지 않습니다. - 지원되지 않는 명령어입니다!");
	}
}

/*
 * checkNumOfParameterAndSplitInput() - 명령어 종류에 맞는 인자의 개수가 입력되었는지 확인하고
 *										명령어 종류에 맞게 명령어를 벡터 inputSplit으로 분리한다.
 */
void Console::checkNumOfParameterAndSplitInput(string& anInput, vector<string>& anInputSplit) {
	//먼저 anInput에서 명령어에 해당하는 부분을 벡터에 push 하고 anInput에서 삭제한다.
	anInputSplit.push_back(anInput.substr(0, 1));
	anInput.erase(0, 1);

	//','의 개수를 세어 인자의 개수를 확인해 오류를 검증할 때 사용한다.
	int numOfComma = 0;
	for (int c = anInput.length(); c > 0; c--) {
		if (anInput[c - 1] == ',') {
			numOfComma++;
		}
	}

	//','로 인자를 구분해 벡터에 인자들을 차례로 넣는다.
	//이때 명령어 별로 필요한 인자의 수가 다르기 때문에 명령어 별로 다르게 split을 구현한다.
	//필요한 자료구조들을 먼저 선언하고 실제 구현은 명령어 별로 한다.
	stringstream split(anInput);
	string temp;
	int numOfSplit = 0;

	if (anInputSplit[0] == "i") {
		//i 명령어는 3개의 인자가 필요하다. 따라서 2번의 필수 split을 거친다.
		//또한 ","의 수도 2개 이상 있어야 한다.
		numOfSplit = 2;
	}
	else if (anInputSplit[0] == "d") {
		numOfSplit = 1;
	}
	else if (anInputSplit[0] == "s") {
		numOfSplit = 0;
	}
	else if (anInputSplit[0] == "c") {
		numOfSplit = 1;
	}
	else {
		throw string("명령어가 올바르지 않습니다. - 지원되지 않는 명령어입니다!");
	}


	//","의 개수가 명령어 별로 정해진 수만큼 존재하는지 확인한다.
	if (numOfComma < numOfSplit) {
		throw string("명령어가 올바르지 않습니다. - ") + anInputSplit[0] + string(" 명령어의 인자 개수는 ") + to_string(numOfSplit + 1) + string("개여야 합니다!");
	}
	//최소 (numOfSplit+1)개의 인자가 있는 것으로 확인되었다.
	//인자들을 벡터로 분리한다.
	//이때, 문자열에 입력될 수 있는 인자에는 ","가 포함될 수 있음을 고려해야 한다.
	for (int c = numOfSplit; c > 0; c--) {
		getline(split, temp, ',');
		anInputSplit.push_back(temp);
	}
	getline(split, temp); //stringstream split에 남은 모든 문자열을 temp로 저장
	anInputSplit.push_back(temp); //3번째 인자를 벡터에 push
}

/*
 * is_integer() - 주어진 string이 정수인지를 반환하는 함수
 *				  정수가 맞으면 true를 리턴한다.
 */
bool Console::is_integer(string test) {
	//먼저 atoi()를 활용해서 해당 문자열이 숫자가 아니면 0을 반환한다.
	//이때 숫자가 0이면 구분이 불가능하므로 string의 compare() 함수를 활용하여
	//실제 문자열이 0일경우에도 true를 반환하도록 한다.
	if (atoi(test.c_str()) != 0 || test.compare("0") == 0) {

		//주어진 string은 숫자가 맞다. 따라서 정수인지 판별한다.
		if (atof(test.c_str()) == (float)atoi(test.c_str())) {
			//실수로 변환한 string과 정수로 변환하고 다시 실수로 변환한 두 수가 같다.
			//따라서 주어진 string은 정수이다.
			return true;
		}
		else {
			return false;
		}

	}
	else {
		//주어진 string은 숫자가 아니다.
		return false;
	}
}

/* stringToInt() - 주어진 string을 정수로 변환한다.
 *				   반드시 해당 string이 정수임이 확실할 때만 사용해야 한다.
 */
int Console::stringToInt(string test) {
	return atoi(test.c_str());
}

