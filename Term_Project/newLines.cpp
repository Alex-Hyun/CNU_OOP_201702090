#include "newLines.h"

/*
 * initializeVector() - ���� �ý��ۿ��� ������ �о�� ���Ϳ� �ܾ� ������ �����ϰ� Ŀ���� ��ġ�� �����Ѵ�.
 */
void Console::initializeVector() {
	string word;
	ifstream file("test.txt");

	if (file.is_open()) {
		while (file) {
			while (getline(file, word, ' ')) { //file���� ������ �������� �ܾ �о�´�.
				newLines.push_back(word); //�о�� �ܾ ��� ���Ϳ� push �Ѵ�.
			}
		}
		file.close(); // ���� �ݱ�
		current_cursor = 0; //Ŀ�� �ʱ�ȭ
	}
	else cout << "�ֿܼ��� �۾��� ������ �ҷ����µ� �����Ͽ����ϴ�." << endl;
}

/*
 * printConsole() - ���� ������ ���� �������� �ܼ�â�� ����Ѵ�.
 */
void Console::printConsole(string consoleMessage) {
	system("cls"); //���ݱ����� ����� ����� ���Ӱ� �ܼ�â�� ����Ѵ�.

	/* �ؽ�Ʈ ��� ���� */

	string line; //�ϼ��� ������ �����ϴ� �ӽ� ����. ����� ������ ���� ������ ��´�.
	int byteCount = 0, lineCount = 1; //line(20)�� byte(75)�� ���� �����ϱ� ���� ����ϴ� count ����.
	vector<string>::iterator itr = newLines.begin(); //newLines ������ ���� �ݺ���

	//���� cursor�� ���� index��ŭ �ݺ��ڸ� �̵���Ų��.
	for (int c = current_cursor; c > 0; c--) {
		itr++;
	}
	next_cursor = current_cursor;

	//���� �ݺ��� itr�� ��ġ���� 20lines�� �ֿܼ� ����Ѵ�.
	for (; itr != newLines.end(); itr++) {
		if (lineCount <= 20) { //lineCount�� 20�� ���� �� ����.

			byteCount += itr->length(); //byteCount�� ���� word�� ���̸� �����Ѵ�.

			if (byteCount <= 75) { //byteCount�� 75�� ���� �� ����.
				line += *itr; //line�� ���� �ܾ �߰��Ѵ�.
				line += ' '; //�ܾ� ���̿� ���� �߰�

				byteCount += 1; //byteCount�� ������ �߰��ؼ� ���
			}
			else { //byteCount�� 75�� �Ѿ� line�� �ϼ���
				//�ϼ��� ���� ���
				cout << setw(2) << lineCount << "| " << line << endl;

				//���� �ʱ�ȭ
				line.clear();
				line.resize(0);

				//Count ���� ����
				lineCount += 1;
				byteCount = 0;

				//���ο� line�� ���� word�߰�
				line += *itr;
				line += ' ';
				//���ο� byteCount�� ���� word�� ���� �߰�
				byteCount += itr->length() + 1;
			}
		}
		else break; // lineCount�� 20�� �Ǹ� ����
		next_cursor++;
	}
	next_cursor--;
	//20������ �ʰ����� �ʴ� ���¿��� ������ ������ 75byte�� ���� ���ϸ� ��µ��� �ʴ´�. �̸� ����
	if (byteCount != 75 && itr == newLines.end()) {
		cout << setw(2) << (lineCount == 0 ? 1 : lineCount) << "| " << line << endl;
	}

	/* �ؽ�Ʈ ��� �Ϸ� */

	printConsole_line();

	cout << "n:����������, p:����������, i:����, d:����, c:����, s:ã��, t:����������" << endl;

	printConsole_line();

	cout << consoleMessage << endl; //�Ű������� ���޹��� �ܼ� �޽����� ���

	printConsole_line();

	cout << "�Է� : " << endl;

	printConsole_line();

	//��ɾ� �Է��� ���� Ŀ���� ��ġ�� '�Է�: ' �������� ����
	COORD pos;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

	pos.X = 7;
	pos.Y = curInfo.dwCursorPosition.Y - 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*
 * printConsole_line() - printConsole()���� ����ϴ� �Լ�, ���� ���п� ���� ���
 */
void Console::printConsole_line() {
	string acrossLine;

	for (int c = 0; c < 83; c++) {
		acrossLine += '-';
	}

	cout << acrossLine << endl;
}

/*
 * nextInput() - ���� ����� �Է¹ް� �ؼ��Ѵ�.
 *				�ؼ��� ��ɴ�� �Լ��� �����ϰ� �Ϸ�� �Լ����� ������ �޽����� main()�Լ��� �����Ѵ�.
 */
string Console::nextInput() {
	string input; //�Է¹޴� ��ɾ� ����
	vector<string> inputSplit; //�Է¹��� ��ɾ �����ؼ� ���Ϳ� ����, checkError���� �����Ѵ�.

	getline(cin, input); //������ ������ ���ڿ��� \n���� �Է¹޴´�.

	/* ��ɾ� ���� üũ */

	try {
		//��ɾ ������ ������ ��ɾ �и��ؼ� ���Ϳ� ������ ���� �����Ѵ�.
		inputSplit = checkError(input);
	}
	catch (string& e) {
		//������ ���� ��� �ش� ���� �޽����� ���� string�� main() ���� �����Ѵ�.
		return e;
	}

	/* ��ɾ� ���� */

	try { //��ɾ �����ϰ� �ش� ��ɾ�� �����ϴ� �޽����� main()���� �����Ѵ�.
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
			//checkError���� ������ �ʴ� ��ɾ üũ�ϹǷ� �ٽ� üũ�� �ʿ� ����.
			break;
		}
	}
	catch (string& e) { //��ɾ� ���� �Լ����� ������ �߻��� ��� �۵��� ���߰� �ش� ���� �޽����� main()���� �����Ѵ�.
		return e;
	}
	catch (int& e) { //t_saveAndExit()���� �ܼ��� �����ϱ� ���� flow
		return "exit";
	}

}

/*
 * checkError() - �Էµ� ��ɾ��� ���� ���θ� üũ�ϰ� ��ɾ split�� inputSplit�� �����Ѵ�.
 *				 ������ �߰ߵǸ� nextInput() �Լ��� ���ܸ� throw�Ѵ�.
 */
vector<string> Console::checkError(string input) {

	vector<string> inputSplit;

	//���� ���� ��ɾ ������ ������ ���� ó��
	if (input.find(" ") != string::npos) {
		throw string("��ɾ �ùٸ��� �ʽ��ϴ�. - ��ɾ ������ �����մϴ�!");
	}
	if (input.length() == 0) {
		throw string("��ɾ �ùٸ��� �ʽ��ϴ�. - ��ɾ �Է����ּ���!");
	}

	/*
	 * ��ɾ� �� ���� üũ
	 */

	 //1. t, n, p ��ɾ�� ���ڰ� �����Ƿ� ��ɾ�ڿ� ���ʿ��� ���ڰ� �ִ����� �˻��Ѵ�.
	if (input[0] == 't' || input[0] == 'n' || input[0] == 'p') {
		if (input.length() != 1) {
			throw string("��ɾ �ùٸ��� �ʽ��ϴ�. - ���ʿ��� ���ڰ� �����մϴ�!");
		}
		else {
			//�������� ��� inputSplit�� ���ڸ� �߰��ϰ� nextInput()���� �����Ѵ�.
			inputSplit.push_back(input);
			return inputSplit;
		}
	}

	//2. i, d, s, c ��ɾ�� ���ڰ� �����ϹǷ� ��ɾ �и��ؼ� �˻��Ѵ�.

	//2-1. ���� ��ȣ�� ����� �Է��ߴ��� �˻��ϰ� �ùٸ��ٸ� ��ȣ�� �����Ѵ�.
	if (!(input.substr(1, 1) == "(" && *(input.end() - 1) == ')')) {
		throw string("��ɾ �ùٸ��� �ʽ��ϴ�. - '��ɾ�(����)'�� ������ �����ּ���!");
	}
	else {
		//��ȣ�� �����.
		input.erase(1, 1);
		input.pop_back();
	}

	//2-2. ��ɾ��� ���� ������ �ùٸ��� Ȯ���ϰ� ��ɾ ���� inputSplit���� �и��Ѵ�.
	checkNumOfParameterAndSplitInput(input, inputSplit);

	//2-3. ���Ϳ� ����� ���ڸ� �������� ��Ȯ�� ��ɾ �ԷµǾ����� Ȯ���Ѵ�.
	if (inputSplit[0] == "i") {

		//ù��°, �ι�° ���ڿ� ������ �ƴ� ���ڰ� �ԷµǸ� ����
		if (!is_integer(inputSplit[1]) || !is_integer(inputSplit[2])) {
			throw string("��ɾ �ùٸ��� �ʽ��ϴ�. - i ��ɾ��� 1,2�� ���ڴ� �������� �մϴ�!");
		}
		//line�� �ǹ��ϴ� ù ��° ���ڰ� 0���ϰų� 20�ʰ��̸� ����
		if ((stringToInt(inputSplit[1]) <= 0) || (stringToInt(inputSplit[1]) > 20)) {
			throw string("��ɾ �ùٸ��� �ʽ��ϴ�. - i ��ɾ��� 1�� ���ڴ� 1�� 20 ������ ������ �մϴ�!");
		}
		//word�� �ǹ��ϴ� �� ��° ���ڰ� 0���ϸ� ����
		if ((stringToInt(inputSplit[2]) < 0)) {
			throw string("��ɾ �ùٸ��� �ʽ��ϴ�. - i ��ɾ��� 2�� ���ڴ� 0�̻��̾�� �մϴ�!");
		}
		//������ ���ڿ��� �ǹ��ϴ� �� ��° ���ڴ� 75����Ʈ�� �ʰ��� �� ����.
		if (inputSplit[3].length() > 75) {
			throw string("��ɾ �ùٸ��� �ʽ��ϴ�. - i ��ɾ��� 3�� ���ڴ� 75����Ʈ�� �ʰ��� �� �����ϴ�!");
		}

		//������ ������ ���͸� �����Ѵ�.
		return inputSplit;
	}
	else if (inputSplit[0] == "d") {

		//ù��°, �ι�° ���ڿ� ������ �ƴ� ���ڰ� �ԷµǸ� ����
		if (!is_integer(inputSplit[1]) || !is_integer(inputSplit[2])) {
			throw string("��ɾ �ùٸ��� �ʽ��ϴ�. - d ��ɾ��� �� ���ڴ� �������� �մϴ�!");
		}
		//line�� �ǹ��ϴ� ù ��° ���ڰ� 0���ϰų� 20�ʰ��̸� ����
		if ((stringToInt(inputSplit[1]) <= 0) || (stringToInt(inputSplit[1]) > 20)) {
			throw string("��ɾ �ùٸ��� �ʽ��ϴ�. - d ��ɾ��� 1�� ���ڴ� 1�� 20 ������ ������ �մϴ�!");
		}
		//word�� �ǹ��ϴ� �� ��° ���ڰ� 0���ϸ� ����
		if ((stringToInt(inputSplit[2]) <= 0)) {
			throw string("��ɾ �ùٸ��� �ʽ��ϴ�. - d ��ɾ��� 2�� ���ڴ� 1�̻��̾�� �մϴ�!");
		}

		//������ ������ ���͸� �����Ѵ�.
		return inputSplit;
	}
	else if (inputSplit[0] == "s") {

		if ((inputSplit[1].length() > 75)) {
			throw string("��ɾ �ùٸ��� �ʽ��ϴ�. - s ��ɾ��� ���ڴ� 75����Ʈ�� �ʰ��� �� �����ϴ�!");
		}

		//������ ������ ���͸� �����Ѵ�.
		return inputSplit;
	}
	else if (inputSplit[0] == "c") {

		//�� ���ڰ� 75byte�� �ʰ��ϸ� ����
		if ((inputSplit[1].length() > 75) || (inputSplit[2].length() > 75)) {
			throw string("��ɾ �ùٸ��� �ʽ��ϴ�. - c ��ɾ��� �� ���ڴ� 75����Ʈ�� �ʰ��� �� �����ϴ�!");
		}
		//������ ������ ���͸� �����Ѵ�.
		return inputSplit;
	}
	else { //��ɾ��� ù ���ڰ� �������� ���� ������ ���
		throw string("��ɾ �ùٸ��� �ʽ��ϴ�. - �������� �ʴ� ��ɾ��Դϴ�!");
	}
}

/*
 * checkNumOfParameterAndSplitInput() - ��ɾ� ������ �´� ������ ������ �ԷµǾ����� Ȯ���ϰ�
 *										��ɾ� ������ �°� ��ɾ ���� inputSplit���� �и��Ѵ�.
 */
void Console::checkNumOfParameterAndSplitInput(string& anInput, vector<string>& anInputSplit) {
	//���� anInput���� ��ɾ �ش��ϴ� �κ��� ���Ϳ� push �ϰ� anInput���� �����Ѵ�.
	anInputSplit.push_back(anInput.substr(0, 1));
	anInput.erase(0, 1);

	//','�� ������ ���� ������ ������ Ȯ���� ������ ������ �� ����Ѵ�.
	int numOfComma = 0;
	for (int c = anInput.length(); c > 0; c--) {
		if (anInput[c - 1] == ',') {
			numOfComma++;
		}
	}

	//','�� ���ڸ� ������ ���Ϳ� ���ڵ��� ���ʷ� �ִ´�.
	//�̶� ��ɾ� ���� �ʿ��� ������ ���� �ٸ��� ������ ��ɾ� ���� �ٸ��� split�� �����Ѵ�.
	//�ʿ��� �ڷᱸ������ ���� �����ϰ� ���� ������ ��ɾ� ���� �Ѵ�.
	stringstream split(anInput);
	string temp;
	int numOfSplit = 0;

	if (anInputSplit[0] == "i") {
		//i ��ɾ�� 3���� ���ڰ� �ʿ��ϴ�. ���� 2���� �ʼ� split�� ��ģ��.
		//���� ","�� ���� 2�� �̻� �־�� �Ѵ�.
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
		throw string("��ɾ �ùٸ��� �ʽ��ϴ�. - �������� �ʴ� ��ɾ��Դϴ�!");
	}


	//","�� ������ ��ɾ� ���� ������ ����ŭ �����ϴ��� Ȯ���Ѵ�.
	if (numOfComma < numOfSplit) {
		throw string("��ɾ �ùٸ��� �ʽ��ϴ�. - ") + anInputSplit[0] + string(" ��ɾ��� ���� ������ ") + to_string(numOfSplit + 1) + string("������ �մϴ�!");
	}
	//�ּ� (numOfSplit+1)���� ���ڰ� �ִ� ������ Ȯ�εǾ���.
	//���ڵ��� ���ͷ� �и��Ѵ�.
	//�̶�, ���ڿ��� �Էµ� �� �ִ� ���ڿ��� ","�� ���Ե� �� ������ ����ؾ� �Ѵ�.
	for (int c = numOfSplit; c > 0; c--) {
		getline(split, temp, ',');
		anInputSplit.push_back(temp);
	}
	getline(split, temp); //stringstream split�� ���� ��� ���ڿ��� temp�� ����
	anInputSplit.push_back(temp); //3��° ���ڸ� ���Ϳ� push
}

/*
 * is_integer() - �־��� string�� ���������� ��ȯ�ϴ� �Լ�
 *				  ������ ������ true�� �����Ѵ�.
 */
bool Console::is_integer(string test) {
	//���� atoi()�� Ȱ���ؼ� �ش� ���ڿ��� ���ڰ� �ƴϸ� 0�� ��ȯ�Ѵ�.
	//�̶� ���ڰ� 0�̸� ������ �Ұ����ϹǷ� string�� compare() �Լ��� Ȱ���Ͽ�
	//���� ���ڿ��� 0�ϰ�쿡�� true�� ��ȯ�ϵ��� �Ѵ�.
	if (atoi(test.c_str()) != 0 || test.compare("0") == 0) {

		//�־��� string�� ���ڰ� �´�. ���� �������� �Ǻ��Ѵ�.
		if (atof(test.c_str()) == (float)atoi(test.c_str())) {
			//�Ǽ��� ��ȯ�� string�� ������ ��ȯ�ϰ� �ٽ� �Ǽ��� ��ȯ�� �� ���� ����.
			//���� �־��� string�� �����̴�.
			return true;
		}
		else {
			return false;
		}

	}
	else {
		//�־��� string�� ���ڰ� �ƴϴ�.
		return false;
	}
}

/* stringToInt() - �־��� string�� ������ ��ȯ�Ѵ�.
 *				   �ݵ�� �ش� string�� �������� Ȯ���� ���� ����ؾ� �Ѵ�.
 */
int Console::stringToInt(string test) {
	return atoi(test.c_str());
}

