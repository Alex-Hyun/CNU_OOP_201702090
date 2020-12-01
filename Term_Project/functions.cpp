#include "newLines.h"


/*
 * givenIterator() - ���Ϳ��� �Է��� line, word�� ã�� �ش� �ݺ��ڸ� �����Ѵ�.
 */
vector<string>::iterator Console::givenIterator(int line, int word) {
	int givenLine = line;
	int givenWord = word;

	//���� cursor�� ���� index��ŭ �ݺ��ڸ� �̵���Ų��.
	vector<string>::iterator itr = newLines.begin();
	for (int c = current_cursor; c > 0; c--) {
		itr++;
	}

	//���� itr�� cursor�� ����ȭ �Ǿ���.
	//���� ���Ϳ��� �־��� line, word�� �ܾ ã�´�.

	//���� line�� ã�´�.
	int byteCount = 0;
	while ((givenLine - 1) > 0) {
		byteCount += itr->length(); //byteCount�� ���� word�� ���̸� �����Ѵ�.

		if (byteCount <= 75) { //byteCount�� 75�� ���� �� ����.
			byteCount += 1; //byteCount�� ������ �߰��ؼ� ���
		}
		else { //byteCount�� 75�� �Ѿ� line�� �ϼ���
			//byteCount �ʱ�ȭ
			byteCount = 0;
			//���ο� byteCount�� ���� word�� ���� �߰�
			byteCount += itr->length() + 1;
			//line 1 ����
			givenLine--;
		}

		//���� �ܾ�� �̵�
		itr++;
	}
	// ù ��° line���� Ž���� �ϴ� ��츦 �����ϰ� (while-loop�� �������� ����)
	// itr�� for���� ���� �� �� �� �������� ���� �����Ѵ�. (lineCount�� 20�� �ʰ��ص� �������� �� �� �� ��������.)
	if (line != 1) itr--;

	//line�� ã�Ҵ�. ���� word�� ã�´�. ���������� byteCount�� �����ָ� Ž���� �����Ѵ�.
	//���� word�� ã�ٰ� byteCount�� 75�� �ʰ��ϸ� ���� �������� �Ѿ ������ �����ϰ� ������ ����ؾ� �Ѵ�.
	//�̸� ���� byteCount ������ ���� �ʱ�ȭ ���ش�.
	byteCount = 0;

	for (; givenWord > 0; givenWord--) {
		itr++;
		byteCount += itr->length() + 1;
		if (byteCount > 75) {
			throw string("��ɾ �ùٸ��� �ʽ��ϴ�. - ") + to_string(line) + string("���ο��� ") + to_string(word) + string("��° �ܾ �������� �ʽ��ϴ�!");
		}
	}

	//insert�� ��� givenWord�� 0�� �� ���� �����Ƿ� for-loop�� ��ġ�� itr���� 1�� ���ش�.
	//�̷��� �ϸ� givenWord�� 1�� �� �ش� ������ ù ��° �ܾ ����Ű�� �ȴ�.
	itr--;

	//�־��� line�� �־��� word�� ����Ű�� �����͸� ��ȯ�Ѵ�.
	return itr;
}

/*
 * i_insertWord() - �Է��� ���ΰ� �ܾ�ڿ� ���ڿ��� �����Ѵ�.
 */
string Console::i_insertWord(vector<string> inputSplit) {
	//insert ����
	int line = stringToInt(inputSplit[1]); //�߰��� �ܾ��� ���� ��ȣ
	int word = stringToInt(inputSplit[2]); //�߰��� �ܾ� ������ �ܾ� ��ȣ
	vector<string>::iterator itr;

	//���� line == 1 �̰� word == 0�̸鼭 ���� ��� ���� �������� ù �������� ���
	//givenIterator() �Լ����� ������ ������ ���� ó���� �Ұ��ϹǷ� if���� ���� ���� ó�����ش�.
	if ((line == 1 && word == 0) && current_cursor == 0) {
		newLines.emplace(newLines.begin(), inputSplit[3]);
		return inputSplit[1] + string("��° ������ ") + inputSplit[2] + string("��° �ܾ� �ڿ� �ܾ� \"") + inputSplit[3] + string("\"�� �����߽��ϴ�");
	}
	//������ ��쿡�� inputSplit�� ���� �־��� ��ɾ��� ���ڸ� line, word�� ���� �ݺ��ڸ� ��´�.
	else {
		itr = givenIterator(line, word); //���ڷ� ���� line�� word�� ����Ű�� �ܾ �����Ѵ�.
		//�ش� �ݺ��� �ڿ� �ܾ �����ؾ� �ϹǷ� itr�� 1�� �����ش�.
		itr += 1;
		newLines.emplace(itr, inputSplit[3]);
		return inputSplit[1] + string("��° ������ ") + inputSplit[2] + string("��° �ܾ� �ڿ� �ܾ� \"") + inputSplit[3] + string("\"�� �����߽��ϴ�");
	}

}

/*
 * d_deleteWord() - �Է��� ���ΰ� �ܾ��� ������ �����Ѵ�.
 */
string Console::d_deleteWord(vector<string> inputSplit) {
	int line = stringToInt(inputSplit[1]); //�߰��� �ܾ��� ���� ��ȣ
	int word = stringToInt(inputSplit[2]); //�߰��� �ܾ� ������ �ܾ� ��ȣ

	//inputSplit�� ���� �־��� ��ɾ��� ���ڸ� line, word�� ���� �ݺ��ڸ� ��´�.
	vector<string>::iterator itr = givenIterator(line, word);

	//�ش� �ݺ��ڰ� ����Ű�� �ܾ �����Ѵ�.
	newLines.erase(itr);

	return inputSplit[1] + string("��° ������ ") + inputSplit[2] + string("��° �ܾ �����߽��ϴ�.");
}
/*
* s_realign() - �Է��� ���ڿ��� ��ü ���Ͽ��� ã�� �ܼ��� �� ������ ��ġ��Ų��.
*/
string Console::s_realign(vector<string> inputSplit) {
	int newCursor = -1;

	for (vector<string>::iterator itr = newLines.begin(); itr != newLines.end(); itr++) {
		newCursor++;
		if (*itr == inputSplit[1]) {
			//��ɾ�� �־��� �ܾ�� ��ġ�ϴ� �ܾ ã��
			//�������� cursor�� newCursor�� �����Ѵ�.
			current_cursor = newCursor;
			return string("�־��� �ܾ� \"") + inputSplit[1] + string("\"�� ã�ҽ��ϴ�. �ܼ��� ù ���ο� ����մϴ�.");
		}
	}

	throw string("�־��� �ܾ� \"") + inputSplit[1] + string("\"�� ���Ͽ� �������� �ʽ��ϴ�!");
}
/*
* c_changeWord() - �Է��� ù ��° ���ڿ��� ��� �� ��° ���ڿ��� �����Ѵ�.
*/
string Console::c_changeWord(vector<string> inputSplit) {
	//��� inputSplit[1]�� ã�� inputSplit[2]�� �����Ѵ�.
	for (int c = newLines.size(); c > 0; c--) {
		if (newLines.at(c - 1) == inputSplit[1]) {
			newLines.at(c - 1) = (inputSplit[2]);
		}
	}

	return string("��ü �ؽ�Ʈ���� ��� ") + inputSplit[1] + string("�� ã�� ") + inputSplit[2] + string("�� �����߽��ϴ�.");
}
/*
* t_saveAndExit() - ���ݱ��� �۾��� ������ txt ���Ͽ� �����ϰ� �ܼ��� �����Ѵ�.
*/
string Console::t_saveAndExit() {
	ofstream file("test.txt");

	if (file.is_open()) {
		for (int i = newLines.size(); i > 0; i--) {
			if (i == 1) {
				//���������� ���� �����ϰ� ����
				file << newLines[newLines.size() - i];
				break;
			}
			file << newLines[newLines.size() - i] << " ";
		}
		file.close();
	}
	else {
		throw string("�۾� ������ ���Ͽ� �����ϴµ� �����Ͽ����ϴ�!");
	}

	throw int(1); //nextInput()���� �ܼ��� ���Ḧ �˸���.

	return string(""); //���� �帧�̶�� �̰����� �������� �ʴ´�.
}
/*
* n_nextPage() - ���� �������� ����Ѵ�.
*/
string Console::n_nextPage() {
	vector<string>::iterator itr = newLines.begin();

	//print_console�� ���ڿ��� ������ ���� ����� ��ġ�� next_consor�� ������ size�� ����� �ȴ�.
	//���� �̶��� �ٷ� p_previousPage()�Լ��� �������ش�.
	if (next_cursor > newLines.size()) {
		return p_previousPage(true);
	}

	//itr�� ���� ��¹��� ù �ܾ ����Ű���� �̵���Ų��.
	for (int c = next_cursor; c > 0; c--) {
		itr++;
	}

	//�� ������ itr�� ���� 20 ������ �����ϴ��� ����Ѵ�.
	//20 ������ itr ���Ŀ� �������� ������ ������ �ܾ�� ���� 20 ������ ����ϵ��� cursor�� �����Ѵ�.

	int byteCount = 0, lineCount = 1;

	for (; itr != newLines.end(); itr++) {
		if (lineCount <= 20) { //lineCount�� 20�� ���� �� ����.

			byteCount += itr->length(); //byteCount�� ���� word�� ���̸� �����Ѵ�.

			if (byteCount <= 75) { //byteCount�� 75�� ���� �� ����.
				byteCount += 1; //byteCount�� ������ �߰��ؼ� ���
			}
			else { //byteCount�� 75�� �Ѿ� line�� �ϼ���
				//Count ���� ����
				lineCount += 1;
				//���ο� byteCount�� ���� word�� ���� �߰�
				byteCount = itr->length() + 1;
			}
		}
		else break; // lineCount�� 20�� �Ǹ� ����
	}

	if (lineCount < 20) {
		//���� �������� ���̰� 20���� �̸��� ���
		//p_previousPage()�� �ڵ带 Ȱ���ؼ� ������ 20������ ����Ѵ�.
		return p_previousPage(true);
	}
	else { //���� �������� ���̰� 20���� �̻��� ���
		current_cursor = next_cursor; //���� Ŀ���� ���� Ŀ���� ���������� �����Ѵ�.
		return string("���� �������� ����մϴ�.");
	}


}
/*
* p_previousPage() - ���� �������� ����Ѵ�.
* ���� ��� ���� 1������ ù �ܾ��� ���� �ܾ ���ο� ����� ������ �ܾ�� ����ϵ��� cursor�� �����Ѵ�.
*/
string Console::p_previousPage(bool usedByNextPageFunc) {
	//���� cursor�� 1������ ù �ܾ ����Ų��.
	//���� cursor�� ��ġ�� �ݺ��ڿ��� ������Ű�� �ݺ���-1���� 20������ ������ ����ؼ�
	//1���ο� �ٽ� ���� �Ǵ� �ݺ��ڸ� ���ϰ� �̸� �ٽ� cursorȭ ��Ų��.

	if (current_cursor == 0) {
		throw string("���� �������� �����ϴ� - ù ������ �Դϴ�!");
	}

	vector<string>::iterator itr = newLines.begin();

	//������������ ����ϱ� ���� �� �Լ��� ����ϸ� cursor�� itr�� ������ ���� cursor�� �� �ܾ���� ����ϰ� �ǰ�
	if (usedByNextPageFunc == false) {
		for (int c = current_cursor; c > 0; c--) {
			itr++;
		}

		itr--;
		current_cursor--; //�� �������� itr�� cursor�� ���ο� �ܼ� ����� ���� ������ �ܾ ����Ų��.
	}
	//nextPage()���� ������ 20 ������ ����ϱ� �� �Լ��� ����ϸ� current_cursor�� ������ ������ �ܾ ����Ű�� �ȴ�.
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
		else break; //20������ �Ѿ�� Ž�� ����

		if (itr == newLines.begin()) {
			//itr������ �����ϰ��� begin()�� �����ϸ� break�� for-loop�� Ż���Ѵ�.
			break;
		}
		current_cursor--;
		itr--;
	}
	//for-loop�� ����Ǿ��� �� lineCount�� ���� 20�̸��̸� ���� ������ ������ 20 ������ �������� �ʴ� ���̴�.
	//���� Ŀ���� ������ ù �ܾ�� �̵���Ų��.
	if (lineCount < 20) {
		current_cursor = 0;
		return string("�ܿ� ������ 20���� �̸��̹Ƿ� ù �������� ����մϴ�.");
	}

	else {
		if (itr == newLines.begin()) {
			current_cursor--;
		}
		current_cursor++;
		if (usedByNextPageFunc == false) { //previousPage()�Լ������� �⺻ ���� ��
			return string("���� �������� ����մϴ�.");
		}
		else { //nextPage() �Լ����� previousPage()�� �ڵ带 ����� �� ���� ��
			return string("���� �������� 20���κ��� ���� ������ 20������ ����մϴ�.");
		}

	}
}