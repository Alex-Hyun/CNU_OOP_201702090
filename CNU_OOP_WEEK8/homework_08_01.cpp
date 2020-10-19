#include <iostream>

class GlobalClass{
private:
	int m_value;
	static GlobalClass* s_instance;

	// private 생성자
	GlobalClass(int v = 0){
		m_value = v;
	}
public:
	int get_value(){
		return m_value;
	}
	void set_value(int v){
		m_value = v;
	}
	static GlobalClass* instance(){
		// 기존에 instance가 존재하지 않으면 
		// 새롭게 객체를 생성해서 s_instance에 저장한다.
		if (s_instance == NULL) {
			s_instance = new GlobalClass;
		}
		// 저장되어 있는 객체를 반환한다.
		return s_instance;
	}
};

// Allocating and initializing GlobalClass's
// static data member.  The pointer is being
// allocated - not the object itself.
GlobalClass* GlobalClass::s_instance = 0;

void foo(void){
	GlobalClass::instance()->set_value(1);
	std::cout << "foo: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
}

void bar(void){
	GlobalClass::instance()->set_value(2);
	std::cout << "bar: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
}

int main(){
	std::cout << "main: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
	foo();
	bar();
}