#pragma once
/*
 * INCLUDE LIBRARIES
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

/*
 * DECLARE SINGLETON CLASS
 */
class Console {
private:
	static Console* instance; //Console�� ���� ������ �ν��Ͻ�
	vector<string> newLines; //���� �������� ���ε��� �����ϴ� �����̳�

	int current_cursor; //���� ��� ���� ���ڿ��� ù �ܾ��� ���Ϳ����� index�� ����ϴ� Ŀ�� ����
	int next_cursor; //���� ��¹� ���ڿ��� ù �ܾ��� ���Ϳ����� index�� ����ϴ� Ŀ�� ����

	/*
	 * Singleton Design Pattern�� ���� private ������
   	 */
	Console() {
		instance = nullptr;
		current_cursor = 0;
		next_cursor = 0;
	}

public:
	/*
	 * ���ڿ� �ʱ�ȭ, ���, ��ɾ� �Է� ���� �Լ� - newLines.cpp
	 */
	static Console* getInstance() {  //������ �ν��Ͻ��� ��� �Լ�, static �Լ��̱� ������ ������Ͽ� �����Ѵ�.
		if (instance == nullptr)
			instance = new Console();

		return instance;
	}
	void initializeVector(); //���� �ý��ۿ��� ������ �о�� ���Ϳ� �ܾ� ������ �����ϰ� Ŀ���� ��ġ�� �����Ѵ�.
	void printConsole(string consoleMessage); //���� ������ ���� �������� �ܼ�â�� ����Ѵ�.
	void printConsole_line(); //printConsole()���� ����ϴ� �Լ�, ���� ���п� ���� ���
	string nextInput(); //���� ����� �Է¹ް� �ؼ��Ѵ�.�ؼ��� ��ɴ�� �Լ��� ����
	vector<string> checkError(string input); //�Էµ� ��ɾ��� ���� ���θ� üũ�ϰ� ��ɾ split�� inputSplit�� �����Ѵ�.
	void checkNumOfParameterAndSplitInput(string& anInput, vector<string>& anInputSplit); //��ɾ� ������ �´� ������ ������ �ԷµǾ����� Ȯ���ϰ�
	bool is_integer(string test); //�־��� string�� ���������� ��ȯ�ϴ� �Լ�
	int stringToInt(string test); //�־��� string�� ������ ��ȯ�Ѵ�.

	/*
	 * ��ɾ� ��� ���� ���� �Լ� - functions.cpp
	 */
	vector<string>::iterator givenIterator(int line, int word); //���Ϳ��� �Է��� line, word�� ã�� �ش� �ݺ��ڸ� �����Ѵ�.
	string i_insertWord(vector<string> inputSplit); //�Է��� ���ΰ� �ܾ�ڿ� ���ڿ��� �����Ѵ�.
	string d_deleteWord(vector<string> inputSplit); //�Է��� ���ΰ� �ܾ��� ������ �����Ѵ�.
	string s_realign(vector<string> inputSplit); //�Է��� ���ڿ��� ��ü ���Ͽ��� ã�� �ܼ��� �� ������ ��ġ��Ų��.
	string c_changeWord(vector<string> inputSplit); //�Է��� ù ��° ���ڿ��� ��� �� ��° ���ڿ��� �����Ѵ�.
	string t_saveAndExit(); //���ݱ��� �۾��� ������ txt ���Ͽ� �����ϰ� �ܼ��� �����Ѵ�.
	string n_nextPage(); //���� �������� ����Ѵ�.
	string p_previousPage(bool usedByNextPageFunc); //���� �������� ����Ѵ�.
};