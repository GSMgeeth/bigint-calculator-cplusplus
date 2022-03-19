//
//  main.cpp
//  calculator
//
//  Created by Geeth Madhushan on 2021-10-13.
//

#include <iostream>
#include <stack>
#include "Bigint.hpp"

int main(int argc, const char * argv[]) {
    
    Bigint* bx = new Bigint();
    std::cin >> *bx;

    Bigint* by = new Bigint();
    std::cin >> *by;

    char opr;
    std::cin >> opr;

    switch (opr) {
        case '+':
            std::cout << operator+ (*bx, *by);
            break;
        case '-':
            std::cout << operator- (*bx, *by);
            break;
        case '*':
            std::cout << operator* (*bx, *by);
            break;
        case '/':
            std::cout << operator/ (*bx, *by);
            break;
            
        default:
            break;
    }
    
    return 0;
}
