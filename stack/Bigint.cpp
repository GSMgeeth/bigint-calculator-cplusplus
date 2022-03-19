//
//  Bigint.cpp
//  calculator
//
//  Created by Geeth Madhushan on 2021-10-13.
//

#include "Bigint.hpp"

Bigint::Bigint() {
//    this->digits = new Stack();
    this->size = 0;
}

Bigint::Bigint(Stack digits) {
    this->digits = digits;
    this->size = sizeof(digits);
}

Bigint::~Bigint() {
    this->freeMemory();
}

void Bigint::pushDigits(const char *digits) {
    const size_t length = strlen(digits);
    
    for (int i = 0; i < length; i++) {
        this->digits.push(digits[i]);
    }
    
    this->size += length;
}

void Bigint::setBigint(const char *digits) {
    this->freeMemory();
    this->pushDigits(digits);
}

void Bigint::freeMemory() {
    if (this->size > 0) {
        this->digits.freeMemory();
        this->size = 0;
    }
}

Bigint addSameNumber(const Bigint& number, const int times) {
    char *initialDigits = (char *) malloc(1);
    initialDigits[0] = '0';
    
    Bigint sum;
    sum.setBigint(initialDigits);
    
    free(initialDigits);
    
    for (int i = 0; i < times; i++) {
        sum = operator+ (number, sum);
    }
    
    return sum;
    
//    Stack stack = number.digits;
//    char *digits = (char *) malloc(number.size);
//    memset(digits, '0', number.size);
//
//    size_t i = number.size - 1;
//    while (!stack.isEmpty()) {
//        digits[i] = stack.pop();
//        i--;
//    }
//
//    Bigint n;
//    n.setBigint(digits);
//
//    if (times > 1) {
//        return operator+ (n, addSameNumber(number, times - 1));
//    } else {
//        return n;
//    }
}

Bigint multiplyByDividendsOfTen(const Bigint& number, const int dividendFirstDigit, const int dividendPowerOfTen) {
    Bigint sameNumberSum = addSameNumber(number, dividendFirstDigit);
    
    for (int i = 0; i < dividendPowerOfTen; i++) {
        sameNumberSum.digits.push('0');
    }
    
    return sameNumberSum;
}

Bigint operator+ (const Bigint& leftOperand, const Bigint& rightOperand) {
    Stack left = leftOperand.digits;
    Stack right = rightOperand.digits;
    
    size_t maxDigitsSize = leftOperand.size > rightOperand.size ? leftOperand.size : rightOperand.size;
    
    char *sum = (char *) malloc(maxDigitsSize + 1);
    memset(sum, '0', maxDigitsSize + 1);
    
    int carry = 0;
    size_t i = maxDigitsSize;
    
    while (!left.isEmpty() or !right.isEmpty()) {
        int res = 0;
        
        if (left.isEmpty()) {
            res = right.pop() - '0' + carry;
        } else if (right.isEmpty()) {
            res = left.pop() - '0' + carry;
        } else {
            res = (left.pop() - '0') + (right.pop() - '0') + carry;
        }
        
        sum[i] = res % 10 + '0';
        carry = res / 10;
        
        i--;
    }
    
    Bigint b;
    b.setBigint(sum);
    
    free(sum);
    
    return b;
}

Bigint operator- (const Bigint& leftOperand, const Bigint& rightOperand) {
    Bigint* b = new Bigint();
    
    return *b;
}

Bigint operator* (const Bigint& leftOperand, const Bigint& rightOperand) {
    Stack left = leftOperand.digits;
    Stack right = rightOperand.digits;
    
    char *initialDigits = (char *) malloc(1);
    initialDigits[0] = '0';
    
    Bigint sum;
    sum.setBigint(initialDigits);
    
    free(initialDigits);
    
    size_t rightSize = rightOperand.size;
    
    for (int i = 0; i < rightSize; i++) {
        sum = operator+ (sum, multiplyByDividendsOfTen(leftOperand, right.pop() - '0', i));
    }
    
    return sum;
}

Bigint operator/ (const Bigint& leftOperand, const Bigint& rightOperand) {
    return operator- (leftOperand, rightOperand);
}

std::ostream& operator<< (std::ostream& out, const Bigint& n) {
    if (n.size > 0) {
        out << n.digits;
    }
    
    return out;
}

std::istream& operator>> (std::istream& in, Bigint& n) {
    char *input = (char *) malloc(MAX_DIGITS_SIZE);
    
    if (input != NULL) {
        in >> input;
        
        n.setBigint(input);

        free(input);
    }
    
    return in;
}
