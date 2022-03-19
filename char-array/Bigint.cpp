//
//  Bigint.cpp
//  bigint calculator
//

#include "Bigint.hpp"

Bigint::Bigint() {
    this->digits = NULL;
    this->size = 0;
    this->isMinus = false;
}

Bigint::~Bigint() {
    this->freeMemory();
}

void Bigint::setBigint(const char digits[], const size_t n) {
    this->freeMemory();
    
    this->digits = (char *) malloc(n);
    
//    strncpy(this->digits, digits, n);
    
    for (int i = 0; i < n; i++) {
        this->digits[i] = digits[i];
    }
    
    this->size += n;
}

void Bigint::freeMemory() {
    this->digits = NULL;
    this->size = 0;
//    if (this->size > 0) {
//        try {
//            free(this->digits);
//        } catch (int exception) {
//            this->digits = NULL;
//        }
//
//        this->size = 0;
//    }
}

Bigint subtractSameNumber(const Bigint& leftOperand, const Bigint& rightOperand, Bigint *times) {
    const bool isSizeSame = leftOperand.size == rightOperand.size;
    const bool isRightLarger = rightOperand.size > leftOperand.size;
    const bool isMinus = isRightLarger or (isSizeSame and rightOperand.digits[0] > leftOperand.digits[0]);
    
    if (!isMinus) {
        char temp[1] = {'1'};
        Bigint one;
        one.setBigint(temp, 1);
        
        *times = operator+ (*times, one);
        
        return operator- (subtractSameNumber(leftOperand, rightOperand, times), rightOperand);
    }
    
    return leftOperand;
}

Bigint addSameNumber(const Bigint& number, const int times) {
    if (times > 1) {
        return operator+ (number, addSameNumber(number, times - 1));
    } else if (times < 1) {
        char zero[1] = {'0'};
        
        Bigint zeroBigint;
        zeroBigint.setBigint(zero, 1);
        
        return zeroBigint;
    }
    
    return number;
}

Bigint multiplyByDividendsOfTen(const Bigint& number, const int dividendFirstDigit, const int dividendPowerOfTen) {
    Bigint sameNumberSum = addSameNumber(number, dividendFirstDigit);

    if (dividendPowerOfTen > 0) {
        char zeros[dividendPowerOfTen];
        
        for (int i = 0; i < dividendPowerOfTen; i++) {
            zeros[i] = '0';
        }
        
//        char *digitsWithTrailingZeros = (char *) malloc(sameNumberSum.size + dividendPowerOfTen);
//        strcat(digitsWithTrailingZeros, sameNumberSum.digits);
//        strcat(digitsWithTrailingZeros, zeros);
        
        char digitsWithTrailingZeros[sameNumberSum.size + dividendPowerOfTen];

        for (size_t i = 0; i < sameNumberSum.size; i++) {
            digitsWithTrailingZeros[i] = sameNumberSum.digits[i];
        }

        for (size_t i = sameNumberSum.size; i < sameNumberSum.size + dividendPowerOfTen; i++) {
            digitsWithTrailingZeros[i] = '0';
        }
        
        sameNumberSum.setBigint(digitsWithTrailingZeros, sameNumberSum.size + dividendPowerOfTen);
    }

    return sameNumberSum;
}

Bigint operator+ (const Bigint& leftOperand, const Bigint& rightOperand) {
    
    Bigint leftOpWithoutLeadingZeros;
    Bigint rightOpWithoutLeadingZeros;
    
    size_t leftZeroCount = 0;
    while (leftOperand.digits[leftZeroCount] == '0') {
        leftZeroCount++;
    }
    
    size_t rightZeroCount = 0;
    while (rightOperand.digits[rightZeroCount] == '0') {
        rightZeroCount++;
    }
    
    char *leftDigitsWithoutLeadingZero;
    
    if (leftZeroCount != leftOperand.size) {
        leftDigitsWithoutLeadingZero = (char *) malloc(leftOperand.size - leftZeroCount);
        strcpy(leftDigitsWithoutLeadingZero, leftOperand.digits + leftZeroCount);
        
        leftOpWithoutLeadingZeros.setBigint(leftDigitsWithoutLeadingZero, leftOperand.size - leftZeroCount);
    } else {
        leftDigitsWithoutLeadingZero = (char *) malloc(1);
        strcpy(leftDigitsWithoutLeadingZero, "0");
        
        leftOpWithoutLeadingZeros.setBigint(leftDigitsWithoutLeadingZero, 1);
    }
    
    free(leftDigitsWithoutLeadingZero);
    
    char *rightDigitsWithoutLeadingZero;
    
    if (rightZeroCount != rightOperand.size) {
        rightDigitsWithoutLeadingZero = (char *) malloc(rightOperand.size - rightZeroCount);
        strcpy(rightDigitsWithoutLeadingZero, rightOperand.digits + rightZeroCount);
        
        rightOpWithoutLeadingZeros.setBigint(rightDigitsWithoutLeadingZero, rightOperand.size - rightZeroCount);
    } else {
        rightDigitsWithoutLeadingZero = (char *) malloc(1);
        strcpy(rightDigitsWithoutLeadingZero, "0");
        
        rightOpWithoutLeadingZeros.setBigint(rightDigitsWithoutLeadingZero, 1);
    }
    
    free(rightDigitsWithoutLeadingZero);
    
    size_t leftSizeWithoutLeadingZeros = leftOperand.size - leftZeroCount;
    size_t rightSizeWithoutLeadingZeros = rightOperand.size - rightZeroCount;
    
    const size_t maxDigitsSize = leftSizeWithoutLeadingZeros > rightSizeWithoutLeadingZeros ? leftSizeWithoutLeadingZeros : rightSizeWithoutLeadingZeros;
    
    char sum[maxDigitsSize + 1];
    
    for (int i = 0; i <= maxDigitsSize; i++) {
        sum[i] = '0';
    }
    
    int carry = 0;
    
    for (size_t i = 1; i <= maxDigitsSize || carry >= 1; i++) {
        const size_t rightIndex = rightOpWithoutLeadingZeros.size - i;
        const size_t leftIndex = leftOpWithoutLeadingZeros.size - i;
        int res = 0;
        
        if (i > maxDigitsSize) {
            res = carry;
        } else if (leftOpWithoutLeadingZeros.size < i) {
            res = rightOpWithoutLeadingZeros.digits[rightIndex] - '0' + carry;
        } else if (rightOpWithoutLeadingZeros.size < i) {
            res = leftOpWithoutLeadingZeros.digits[leftIndex] - '0' + carry;
        } else {
            res = (leftOpWithoutLeadingZeros.digits[leftIndex] - '0') + (rightOpWithoutLeadingZeros.digits[rightIndex] - '0') + carry;
        }
        
        sum[maxDigitsSize + 1 - i] = res % 10 + '0';
        carry = res / 10;
    }
    
    Bigint b;
    b.setBigint(sum, maxDigitsSize + 1);
    
    return b;
}

Bigint operator- (const Bigint& leftOperand, const Bigint& rightOperand) {
    
    Bigint leftOpWithoutLeadingZeros;
    Bigint rightOpWithoutLeadingZeros;
    
    size_t leftZeroCount = 0;
    while (leftOperand.digits[leftZeroCount] == '0') {
        leftZeroCount++;
    }
    
    size_t rightZeroCount = 0;
    while (rightOperand.digits[rightZeroCount] == '0') {
        rightZeroCount++;
    }
    
    char *leftDigitsWithoutLeadingZero;
    
    if (leftZeroCount != leftOperand.size) {
        leftDigitsWithoutLeadingZero = (char *) malloc(leftOperand.size - leftZeroCount);
        strcpy(leftDigitsWithoutLeadingZero, leftOperand.digits + leftZeroCount);
        
        leftOpWithoutLeadingZeros.setBigint(leftDigitsWithoutLeadingZero, leftOperand.size - leftZeroCount);
    } else {
        leftDigitsWithoutLeadingZero = (char *) malloc(1);
        strcpy(leftDigitsWithoutLeadingZero, "0");
        
        leftOpWithoutLeadingZeros.setBigint(leftDigitsWithoutLeadingZero, 1);
    }
    
    free(leftDigitsWithoutLeadingZero);
    
    char *rightDigitsWithoutLeadingZero;
    
    if (rightZeroCount != rightOperand.size) {
        rightDigitsWithoutLeadingZero = (char *) malloc(rightOperand.size - rightZeroCount);
        strcpy(rightDigitsWithoutLeadingZero, rightOperand.digits + rightZeroCount);
        
        rightOpWithoutLeadingZeros.setBigint(rightDigitsWithoutLeadingZero, rightOperand.size - rightZeroCount);
    } else {
        rightDigitsWithoutLeadingZero = (char *) malloc(1);
        strcpy(rightDigitsWithoutLeadingZero, "0");
        
        rightOpWithoutLeadingZeros.setBigint(rightDigitsWithoutLeadingZero, 1);
    }
    
    free(rightDigitsWithoutLeadingZero);
    
    size_t leftSizeWithoutLeadingZeros = leftOperand.size - leftZeroCount;
    size_t rightSizeWithoutLeadingZeros = rightOperand.size - rightZeroCount;
    
    const bool isSizeSame = leftSizeWithoutLeadingZeros == rightSizeWithoutLeadingZeros;
    const bool isRightLarger = rightSizeWithoutLeadingZeros > leftSizeWithoutLeadingZeros;
    const bool isMinus = isRightLarger or (isSizeSame and rightOpWithoutLeadingZeros.digits[0] > leftOpWithoutLeadingZeros.digits[0]);
    
    const size_t maxDigitsSize = isRightLarger ? rightOpWithoutLeadingZeros.size : leftOpWithoutLeadingZeros.size;
    
    char sub[maxDigitsSize];
    
    for (int i = 0; i < maxDigitsSize; i++) {
        sub[i] = '0';
    }
    
    int carried = 0;
    
    const Bigint *largeOperand;
    const Bigint *smallOperand;
    
    if (isMinus) {
        largeOperand = &rightOpWithoutLeadingZeros;
        smallOperand = &leftOpWithoutLeadingZeros;
    } else {
        largeOperand = &leftOpWithoutLeadingZeros;
        smallOperand = &rightOpWithoutLeadingZeros;
    }
    
    for (size_t i = 1; i <= maxDigitsSize; i++) {
        const size_t rightIndex = smallOperand->size - i;
        const size_t leftIndex = largeOperand->size - i;
        int res = 0;
        
        if (smallOperand->size < i) {
            res = largeOperand->digits[leftIndex] - '0' - carried;
            if (res == -1) {
                res += 10;
            } else {
                carried = 0;
            }
        } else {
            if (largeOperand->digits[leftIndex] - carried < smallOperand->digits[rightIndex]) {
                res = largeOperand->digits[leftIndex] - carried + 10 - smallOperand->digits[rightIndex];
                carried = 1;
            } else {
                res = largeOperand->digits[leftIndex] - carried - smallOperand->digits[rightIndex];
                carried = 0;
            }
        }
        
        sub[maxDigitsSize - i] = res + '0';
    }
    
    Bigint b;
    b.setBigint(sub, maxDigitsSize);
    b.isMinus = isMinus;
    
    return b;
}

Bigint operator* (const Bigint& leftOperand, const Bigint& rightOperand) {
    char initialDigits[1] = {'0'};
    
    Bigint sum;
    sum.setBigint(initialDigits, 1);
    
    size_t rightOpSize = rightOperand.size;
    
    for (int i = 0; i < rightOpSize; i++) {
        sum = operator+ (sum, multiplyByDividendsOfTen(leftOperand, rightOperand.digits[rightOpSize - i - 1] - '0', i));
    }
    
    return sum;
}

Bigint operator/ (const Bigint& leftOperand, const Bigint& rightOperand) {
    const bool isSizeSame = leftOperand.size == rightOperand.size;
    const bool isRightLarger = rightOperand.size > leftOperand.size;
    const bool isMinus = isRightLarger or (isSizeSame and rightOperand.digits[0] > leftOperand.digits[0]);
    
    char zero[1] = {'0'};
    char one[1] = {'1'};
    
    Bigint bigOne;
    bigOne.setBigint(one, 1);
    
    Bigint sub;
    sub.setBigint(zero, 1);
    
    if (!isMinus) {
        Bigint temp = leftOperand;
        
        while (true) {
            temp = operator- (temp, rightOperand);
            
            if (temp.isMinus) {
                break;
            } else {
                sub = operator+ (sub, bigOne);
            }
        }
    }
    
    return sub;
}

std::ostream& operator<< (std::ostream& out, const Bigint& n) {
    if (n.size > 0) {
        size_t i = 0;
        while (n.digits[i] == '0') {
            i++;
        }
        
        if (n.isMinus) {
            out << "-";
        }

        char *digitsWithoutLeadingZero;

        if (i != n.size) {
            digitsWithoutLeadingZero = (char *) malloc(n.size - i);
            strcpy(digitsWithoutLeadingZero, n.digits + i);
            
            for (int j = 0; j < n.size - i; j++) {
                if (std::isdigit(digitsWithoutLeadingZero[j])) {
                    out << digitsWithoutLeadingZero[j];
                } else {
                    out << '0';
                }
            }
            
            free(digitsWithoutLeadingZero);
        } else {
            out << "0";
        }

        out << std::endl;
    }

    return out;
}

std::istream& operator>> (std::istream& in, Bigint& n) {
    char *input = (char *) malloc(MAX_DIGITS_SIZE);
    
    if (input != NULL) {
        in >> input;
        
        n.setBigint(input, strlen(input));

        free(input);
    }
    
    return in;
}
