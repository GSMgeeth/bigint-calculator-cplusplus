//
//  Stack.hpp
//  calculator
//
//  Created by Geeth Madhushan on 2021-10-16.
//

#ifndef Stack_hpp
#define Stack_hpp

#include <stdio.h>
#include <iostream>

#endif /* Stack_hpp */

struct Node {
    char digit;
    Node *next;
};

class Stack {
private:
    Node *top;
    size_t size;
    
public:
    Stack();
    ~Stack();
    void push(char digit);
    char pop();
    char peek();
    bool isEmpty();
    void freeMemory();
    
    friend Stack stackcpy(Stack destination, const Stack source);
    
    friend std::ostream& operator<< (std::ostream& out, const Stack& stack);
};
