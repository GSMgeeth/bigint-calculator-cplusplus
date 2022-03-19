//
//  Bigint.hpp
//  bigint calculator
//

#pragma once

#ifndef Bigint_hpp
#define Bigint_hpp

#include <stdio.h>
#include <iostream>

#endif /* Bigint_hpp */

const int MAX_DIGITS_SIZE = 255;

/**
 * Bigint class saves a very large number (upto 255 digits) as separate digits.
 *
 * A Bigint type number is capable of doing common calculations mentioned below;
 * - Adding two Bigint numbers with Operator +
 * - Subtracting two Bigint numbers with Operator -
 * - Multiplying two Bigint numbers with Operator *
 * - Dividing two Bigint numbers with Operator /
 *
 * Bigint type has its own ways of inputting and outputting the holding value.
 * - Outputs the value with Operator <<
 * - Inputs the value with Operator >>
 */
class Bigint {
public:
    Bigint();
    ~Bigint();
    
    /**
     * Operator + adds two Bigints.
     *
     * @param leftOperand The left operand Bigint
     * @param rightOperand The right operand Bigint
     */
    friend Bigint operator+ (const Bigint& leftOperand, const Bigint& rightOperand);

    /**
     * Operator - subtracts two Bigints.
     *
     * @param leftOperand The left operand Bigint
     * @param rightOperand The right operand Bigint
     */
    friend Bigint operator- (const Bigint& leftOperand, const Bigint& rightOperand);

    /**
     * Operator * multiplies two Bigints.
     *
     * @param leftOperand The left operand Bigint
     * @param rightOperand The right operand Bigint
     */
    friend Bigint operator* (const Bigint& leftOperand, const Bigint& rightOperand);

    /**
     * Operator / divides two Bigints.
     *
     * @param leftOperand The left operand Bigint
     * @param rightOperand The right operand Bigint
     */
    friend Bigint operator/ (const Bigint& leftOperand, const Bigint& rightOperand);

    /**
     * Operator << outputs the Bigint value.
     *
     * @param out The output
     * @param n The Bigint that should be output
     */
    friend std::ostream& operator<< (std::ostream& out, const Bigint& n);

    /**
     * Operator >> inputs a Bigint value
     *
     * @param in The input
     * @param n The Bigint that should be input into
     */
    friend std::istream& operator>> (std::istream& in, Bigint& n);
    
private:
    char *digits; // Use Stack whenever possible. It's fast and cheap.
    bool isMinus;
    size_t size;
    
    /**
     * Set Bigint values.
     *
     * @param digits The digits to be set into Bigint
     * @param n The number of digits
     */
    void setBigint(const char *digits, const size_t n);
    
    /**
     * Free Bigint allocated memory.
     */
    void freeMemory();

    /**
     * Subtract a Bigint from another Bigint for t times using recursion.
     *
     * @param leftOperand The Bigint to be subtract from
     * @param rightOperand The Bigint to be subtract
     * @param times The number of times to be subtracted
     */
    friend Bigint subtractSameNumber(const Bigint& leftOperand, const Bigint& rightOperand, Bigint *times);
    
    /**
     * Adds the same Bigint for t times using recursion.
     *
     * @param number The Bigint to be added
     * @param times The number of times to be added
     */
    friend Bigint addSameNumber(const Bigint& number, const int times);

    /**
     * Multiplies a Bigint from a dividend of 10 (ex: 20, 30, 200 etc.).
     * Used in multiplication.
     *
     * @param number The Bigint to be divided.
     * @param dividendFirstDigit The dividend's first digit (ex: 2 of 20, 3 of 30, 2 of 200)
     * @param dividendPowerOfTen The dividend's power of ten (ex: 1 of 10, 1 of 30, 2 of 200)
     */
    friend Bigint multiplyByDividendsOfTen(const Bigint& number, const int dividendFirstDigit, const int dividendPowerOfTen);
};
