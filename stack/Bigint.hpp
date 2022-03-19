//
//  Bigint.hpp
//  calculator
//
//  Created by Geeth Madhushan on 2021-10-13.
//

#ifndef Bigint_hpp
#define Bigint_hpp

#include <stdio.h>
#include <iostream>
#include "Stack/Stack.hpp"

#endif /* Bigint_hpp */

const int MAX_DIGITS_SIZE = 255;

class Bigint {
private:
    Stack digits;
    size_t size;
    
    void pushDigits(const char *digits);
    void setBigint(const char *digits);
    void freeMemory();
    
    friend Bigint addSameNumber(const Bigint& number, const int times);
    friend Bigint multiplyByDividendsOfTen(const Bigint& number, const int dividendFirstDigit, const int dividendPowerOfTen);
    
public:
    Bigint();
    Bigint(Stack digits);
    ~Bigint();
    
    friend Bigint operator+ (const Bigint& leftOperand, const Bigint& rightOperand);
    friend Bigint operator- (const Bigint& leftOperand, const Bigint& rightOperand);
    friend Bigint operator* (const Bigint& leftOperand, const Bigint& rightOperand);
    friend Bigint operator/ (const Bigint& leftOperand, const Bigint& rightOperand);
    
    friend std::ostream& operator<< (std::ostream& out, const Bigint& n);
    friend std::istream& operator>> (std::istream& in, Bigint& n);
};
