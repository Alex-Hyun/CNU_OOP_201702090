#include <iostream>
using namespace std;

// Strategy interface 
class Strategy {
public:
	// interface이므로 pure virtual function으로 선언한다.
	virtual int doOperation(int num1, int num2) = 0;
};

// Concrete Strateg
class OperationAdd : public Strategy {
	int doOperation(int num1, int num2) override{
		return num1 + num2;
	}
};

class OperationMultiply : public Strategy {
	int doOperation(int num1, int num2) override {
		return num1 * num2;
	}
};

class OperationSubtract : public Strategy {
	int doOperation(int num1, int num2) override {
		return num1 - num2;
	}
};

// Contect Class
class Context {
private:
	// Strategy를 저장하는 포인터 변수
	// 항상 하나의 strategy를 유지하고 있어야 함
	Strategy* strategy;

public:
	// Constructor
	Context(Strategy* strategy) :strategy(strategy) {}

	// execute strategy
	int executeStrategy(int num1, int num2) {
		return strategy->doOperation(num1, num2);
	}

	~Context() { delete strategy; } // Prevent Memory Leak
};

// main function
int main() {
	Context* context = new Context(new OperationAdd());
	cout << "10 + 5 = " << context->executeStrategy(10, 5) << endl;
	delete context; // Prevent Memory Leak

	context = new Context(new OperationSubtract());
	cout << "10 - 5 = " << context->executeStrategy(10, 5) << endl;
	delete context; // Prevent Memory Leak

	context = new Context(new OperationMultiply());
	cout << "10 * 5 = " << context->executeStrategy(10, 5) << endl;
	delete context; // Prevent Memory Leak
}
