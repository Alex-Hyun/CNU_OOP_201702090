#include "newLines.h"


/*
 * givenIterator() - 벡터에서 입력한 line, word를 찾고 해당 반복자를 리턴한다.
 */
vector<string>::iterator Console::givenIterator(int line, int word) {
	int givenLine = line;
	int givenWord = word;

	//현재 cursor가 갖는 index만큼 반복자를 이동시킨다.
	vector<string>::iterator itr = newLines.begin();
	for (int c = current_cursor; c > 0; c--) {
		itr++;
	}

	//현재 itr는 cursor와 동기화 되었다.
	//이제 벡터에서 주어진 line, word의 단어를 찾는다.

	//먼저 line을 찾는다.
	int byteCount = 0;
	while ((givenLine - 1) > 0) {
		byteCount += itr->length(); //byteCount에 현재 word의 길이를 저장한다.

		if (byteCount <= 75) { //byteCount는 75를 넘을 수 없다.
			byteCount += 1; //byteCount에 공백을 추가해서 계산
		}
		else { //byteCount가 75를 넘어 line이 완성됨
			//byteCount 초기화
			byteCount = 0;
			//새로운 byteCount에 현재 word의 길이 추가
			byteCount += itr->length() + 1;
			//line 1 감소
			givenLine--;
		}

		//다음 단어로 이동
		itr++;
	}
	// 첫 번째 line에서 탐색을 하는 경우를 제외하고 (while-loop을 수행하지 않음)
	// itr가 for문에 의해 한 번 더 더해지는 것을 보정한다. (lineCount가 20을 초과해도 마지막에 한 번 더 더해진다.)
	if (line != 1) itr--;

	//line을 찾았다. 이제 word를 찾는다. 마찬가지로 byteCount를 더해주며 탐색을 진행한다.
	//만약 word를 찾다가 byteCount가 75를 초과하면 다음 라인으로 넘어간 것으로 간주하고 에러를 출력해야 한다.
	//이를 위해 byteCount 변수를 먼저 초기화 해준다.
	byteCount = 0;

	for (; givenWord > 0; givenWord--) {
		itr++;
		byteCount += itr->length() + 1;
		if (byteCount > 75) {
			throw string("명령어가 올바르지 않습니다. - ") + to_string(line) + string("라인에는 ") + to_string(word) + string("번째 단어가 존재하지 않습니다!");
		}
	}

	//insert의 경우 givenWord가 0이 될 수도 있으므로 for-loop을 마치고 itr에서 1을 빼준다.
	//이렇게 하면 givenWord가 1일 때 해당 라인의 첫 번째 단어를 가리키게 된다.
	itr--;

	//주어진 line의 주어진 word를 가리키는 포인터를 반환한다.
	return itr;
}

/*
 * i_insertWord() - 입력한 라인과 단어뒤에 문자열을 삽입한다.
 */
string Console::i_insertWord(vector<string> inputSplit) {
	//insert 실행
	int line = stringToInt(inputSplit[1]); //추가할 단어의 라인 번호
	int word = stringToInt(inputSplit[2]); //추가할 단어 직전의 단어 번호
	vector<string>::iterator itr;

	//먼저 line == 1 이고 word == 0이면서 현재 출력 중인 페이지가 첫 페이지인 경우
	//givenIterator() 함수에서 포인터 에러로 인해 처리가 불가하므로 if문을 통해 직접 처리해준다.
	if ((line == 1 && word == 0) && current_cursor == 0) {
		newLines.emplace(newLines.begin(), inputSplit[3]);
		return inputSplit[1] + string("번째 라인의 ") + inputSplit[2] + string("번째 단어 뒤에 단어 \"") + inputSplit[3] + string("\"을 삽입했습니다");
	}
	//나머지 경우에는 inputSplit을 통해 주어진 명령어의 인자를 line, word로 갖는 반복자를 얻는다.
	else {
		itr = givenIterator(line, word); //인자로 넣은 line과 word가 가리키는 단어를 리턴한다.
		//해당 반복자 뒤에 단어를 삽입해야 하므로 itr에 1을 더해준다.
		itr += 1;
		newLines.emplace(itr, inputSplit[3]);
		return inputSplit[1] + string("번째 라인의 ") + inputSplit[2] + string("번째 단어 뒤에 단어 \"") + inputSplit[3] + string("\"을 삽입했습니다");
	}

}

/*
 * d_deleteWord() - 입력한 라인과 단어의 원소을 삭제한다.
 */
string Console::d_deleteWord(vector<string> inputSplit) {
	int line = stringToInt(inputSplit[1]); //추가할 단어의 라인 번호
	int word = stringToInt(inputSplit[2]); //추가할 단어 직전의 단어 번호

	//inputSplit을 통해 주어진 명령어의 인자를 line, word로 갖는 반복자를 얻는다.
	vector<string>::iterator itr = givenIterator(line, word);

	//해당 반복자가 가리키는 단어를 삭제한다.
	newLines.erase(itr);

	return inputSplit[1] + string("번째 라인의 ") + inputSplit[2] + string("번째 단어를 삭제했습니다.");
}
/*
* s_realign() - 입력한 문자열을 전체 파일에서 찾아 콘솔의 맨 앞으로 위치시킨다.
*/
string Console::s_realign(vector<string> inputSplit) {
	int newCursor = -1;

	for (vector<string>::iterator itr = newLines.begin(); itr != newLines.end(); itr++) {
		newCursor++;
		if (*itr == inputSplit[1]) {
			//명령어로 주어진 단어와 일치하는 단어를 찾음
			//전역변수 cursor를 newCursor로 변경한다.
			current_cursor = newCursor;
			return string("주어진 단어 \"") + inputSplit[1] + string("\"을 찾았습니다. 콘솔의 첫 라인에 출력합니다.");
		}
	}

	throw string("주어진 단어 \"") + inputSplit[1] + string("\"은 파일에 존재하지 않습니다!");
}
/*
* c_changeWord() - 입력한 첫 번째 문자열을 모두 두 번째 문자열로 변경한다.
*/
string Console::c_changeWord(vector<string> inputSplit) {
	//모든 inputSplit[1]을 찾아 inputSplit[2]로 변경한다.
	for (int c = newLines.size(); c > 0; c--) {
		if (newLines.at(c - 1) == inputSplit[1]) {
			newLines.at(c - 1) = (inputSplit[2]);
		}
	}

	return string("전체 텍스트에서 모든 ") + inputSplit[1] + string("을 찾아 ") + inputSplit[2] + string("로 변경했습니다.");
}
/*
* t_saveAndExit() - 지금까지 작업한 내용을 txt 파일에 저장하고 콘솔을 종료한다.
*/
string Console::t_saveAndExit() {
	ofstream file("test.txt");

	if (file.is_open()) {
		for (int i = newLines.size(); i > 0; i--) {
			if (i == 1) {
				//마지막에는 공백 제외하고 삽입
				file << newLines[newLines.size() - i];
				break;
			}
			file << newLines[newLines.size() - i] << " ";
		}
		file.close();
	}
	else {
		throw string("작업 내용을 파일에 저장하는데 실패하였습니다!");
	}

	throw int(1); //nextInput()으로 콘솔의 종료를 알린다.

	return string(""); //정상 흐름이라면 이곳에는 도달하지 않는다.
}
/*
* n_nextPage() - 다음 페이지를 출력한다.
*/
string Console::n_nextPage() {
	vector<string>::iterator itr = newLines.begin();

	//print_console이 문자열의 마지막 까지 출력을 마치면 next_consor이 벡터의 size를 벗어나게 된다.
	//따라서 이때는 바로 p_previousPage()함수를 실행해준다.
	if (next_cursor > newLines.size()) {
		return p_previousPage(true);
	}

	//itr을 다음 출력문의 첫 단어를 가리키도록 이동시킨다.
	for (int c = next_cursor; c > 0; c--) {
		itr++;
	}

	//현 시점의 itr로 부터 20 라인이 존재하는지 계산한다.
	//20 라인이 itr 이후에 존재하지 않으면 마지막 단어로 부터 20 라인을 출력하도록 cursor를 조정한다.

	int byteCount = 0, lineCount = 1;

	for (; itr != newLines.end(); itr++) {
		if (lineCount <= 20) { //lineCount는 20을 넘을 수 없다.

			byteCount += itr->length(); //byteCount에 현재 word의 길이를 저장한다.

			if (byteCount <= 75) { //byteCount는 75를 넘을 수 없다.
				byteCount += 1; //byteCount에 공백을 추가해서 계산
			}
			else { //byteCount가 75를 넘어 line이 완성됨
				//Count 변수 조정
				lineCount += 1;
				//새로운 byteCount에 현재 word의 길이 추가
				byteCount = itr->length() + 1;
			}
		}
		else break; // lineCount가 20이 되면 종료
	}

	if (lineCount < 20) {
		//다음 페이지의 길이가 20라인 미만인 경우
		//p_previousPage()의 코드를 활용해서 마지막 20라인을 출력한다.
		return p_previousPage(true);
	}
	else { //다음 페이지의 길이가 20라인 이상인 경우
		current_cursor = next_cursor; //현재 커서를 다음 커서로 정상적으로 변경한다.
		return string("다음 페이지를 출력합니다.");
	}


}
/*
* p_previousPage() - 이전 페이지를 출력한다.
* 현재 출력 중인 1라인의 첫 단어의 이전 단어를 새로운 출력의 마지막 단어로 출력하도록 cursor를 조정한다.
*/
string Console::p_previousPage(bool usedByNextPageFunc) {
	//현재 cursor는 1라인의 첫 단어를 가리킨다.
	//따라서 cursor의 위치를 반복자에게 참조시키고 반복자-1부터 20라인을 역으로 계산해서
	//1라인에 다시 오게 되는 반복자를 구하고 이를 다시 cursor화 시킨다.

	if (current_cursor == 0) {
		throw string("이전 페이지가 없습니다 - 첫 페이지 입니다!");
	}

	vector<string>::iterator itr = newLines.begin();

	//이전페이지를 출력하기 위해 이 함수를 사용하면 cursor와 itr을 조정해 현재 cursor의 전 단어까지 출력하게 되고
	if (usedByNextPageFunc == false) {
		for (int c = current_cursor; c > 0; c--) {
			itr++;
		}

		itr--;
		current_cursor--; //현 시점에서 itr와 cursor는 새로운 콘솔 출력의 가장 마지막 단어를 가리킨다.
	}
	//nextPage()에서 마지막 20 라인을 출력하기 이 함수를 사용하면 current_cursor가 벡터의 마지막 단어를 가리키게 된다.
	else {
		itr = newLines.end() - 1;
		current_cursor = newLines.size();
	}

	int byteCount = 0, lineCount = 1;
	while (itr >= newLines.begin()) {
		if (lineCount <= 20) {
			byteCount += itr->length();

			if (byteCount <= 75) {
				byteCount++;
			}
			else {
				lineCount++;
				byteCount = itr->length() + 1;
			}
		}
		else break; //20라인을 넘어가면 탐색 종료

		if (itr == newLines.begin()) {
			//itr에러를 방지하고자 begin()에 도달하면 break로 for-loop을 탈출한다.
			break;
		}
		current_cursor--;
		itr--;
	}
	//for-loop이 종료되었을 때 lineCount의 값이 20미만이면 현재 페이지 이전에 20 라인이 존재하지 않는 것이다.
	//따라서 커서를 파일의 첫 단어로 이동시킨다.
	if (lineCount < 20) {
		current_cursor = 0;
		return string("잔여 라인이 20라인 미만이므로 첫 페이지를 출력합니다.");
	}

	else {
		if (itr == newLines.begin()) {
			current_cursor--;
		}
		current_cursor++;
		if (usedByNextPageFunc == false) { //previousPage()함수에서의 기본 리턴 값
			return string("이전 페이지를 출력합니다.");
		}
		else { //nextPage() 함수에서 previousPage()의 코드를 사용할 때 리턴 값
			return string("다음 페이지가 20라인보다 적어 마지막 20라인을 출력합니다.");
		}

	}
}