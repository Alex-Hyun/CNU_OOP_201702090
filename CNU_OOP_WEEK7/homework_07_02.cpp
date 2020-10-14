﻿#include <iostream>

bool funcA() {
    int c;
    std::cin >> c;
    if (c < 10) //Let's assume this is exception
        throw std::out_of_range("Invalid Input!!");
    return true;
}
int main() {
    try {
        funcA();
    }
    catch (std::out_of_range& e) {
        std::cout << "Exception : " << e.what(); // what()을 통해 예외 객체의 인자를 얻는다.
    }

    return 0;
}