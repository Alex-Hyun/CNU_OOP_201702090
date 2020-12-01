#include "newLines.h"

/* static 변수 선언 */
Console* Console::instance;

int main() {

	system("mode con cols=100 lines=35"); //콘솔 창의 크기를 설정
	string message; //nextInput()의 리턴 값, 콘솔에 출력되는 메시지를 저장하는 변수

	Console* instance = Console::getInstance(); //Singleton 클래스에서 인스턴스 얻기
	instance->initializeVector(); //벡터를 초기화
	instance->printConsole("명령어를 입력하세요."); //초기 콘솔창 출력

	while (message != "exit") { //특정 명령어가 입력될 때 까지 반복해서 작업 수행
		message = instance->nextInput();
		instance->printConsole(message);
	}

	/*
	 * t_saveAndExit() 함수에서 정상적으로 파일을 저장하고 종료하도록 예외를 throw한 경우
	 * 이곳으로 제어가 넘어온다.
	 */
	instance->printConsole("작업 내용을 파일에 저장하였습니다. 잠시 후에 콘솔을 종료합니다.");
	Sleep(2000);

	system("cls");
	cout << "콘솔이 종료되었습니다." << endl;
	system("exit");

	return 0;
}