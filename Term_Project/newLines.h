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
	static Console* instance; //Console에 대한 유일한 인스턴스
	vector<string> newLines; //현재 변경중인 라인들을 저장하는 컨테이너

	int current_cursor; //현재 출력 중인 문자열의 첫 단어의 벡터에서의 index를 기억하는 커서 변수
	int next_cursor; //다음 출력문 문자열의 첫 단어의 벡터에서의 index를 기억하는 커서 변수

	/*
	 * Singleton Design Pattern에 따른 private 생성자
   	 */
	Console() {
		instance = nullptr;
		current_cursor = 0;
		next_cursor = 0;
	}

public:
	/*
	 * 문자열 초기화, 출력, 명령어 입력 관련 함수 - newLines.cpp
	 */
	static Console* getInstance() {  //유일한 인스턴스를 얻는 함수, static 함수이기 때문에 헤더파일에 정의한다.
		if (instance == nullptr)
			instance = new Console();

		return instance;
	}
	void initializeVector(); //파일 시스템에서 라인을 읽어와 벡터에 단어 단위로 삽입하고 커서의 위치를 정의한다.
	void printConsole(string consoleMessage); //현재 벡터의 값을 기준으로 콘솔창을 출력한다.
	void printConsole_line(); //printConsole()에서 사용하는 함수, 구역 구분용 선을 출력
	string nextInput(); //다음 명령을 입력받고 해석한다.해석한 명령대로 함수를 실행
	vector<string> checkError(string input); //입력된 명령어의 오류 여부를 체크하고 명령어를 split한 inputSplit을 제공한다.
	void checkNumOfParameterAndSplitInput(string& anInput, vector<string>& anInputSplit); //명령어 종류에 맞는 인자의 개수가 입력되었는지 확인하고
	bool is_integer(string test); //주어진 string이 정수인지를 반환하는 함수
	int stringToInt(string test); //주어진 string을 정수로 변환한다.

	/*
	 * 명령어 기능 구현 관련 함수 - functions.cpp
	 */
	vector<string>::iterator givenIterator(int line, int word); //벡터에서 입력한 line, word를 찾고 해당 반복자를 리턴한다.
	string i_insertWord(vector<string> inputSplit); //입력한 라인과 단어뒤에 문자열을 삽입한다.
	string d_deleteWord(vector<string> inputSplit); //입력한 라인과 단어의 원소을 삭제한다.
	string s_realign(vector<string> inputSplit); //입력한 문자열을 전체 파일에서 찾아 콘솔의 맨 앞으로 위치시킨다.
	string c_changeWord(vector<string> inputSplit); //입력한 첫 번째 문자열을 모두 두 번째 문자열로 변경한다.
	string t_saveAndExit(); //지금까지 작업한 내용을 txt 파일에 저장하고 콘솔을 종료한다.
	string n_nextPage(); //다음 페이지를 출력한다.
	string p_previousPage(bool usedByNextPageFunc); //이전 페이지를 출력한다.
};