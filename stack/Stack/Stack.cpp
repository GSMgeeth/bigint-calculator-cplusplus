//
//  Stack.cpp
//  calculator
//
//  Created by Geeth Madhushan on 2021-10-16.
//

#include "Stack.hpp"

Stack::Stack() {
    top = NULL;
    size = 0;
}

Stack::~Stack() {
    this->freeMemory();
}

void Stack::push(char digit) {
    Node *temp = new Node;
    temp->digit = digit;
    temp->next = top;
    
    top = temp;
    ++size;
}

char Stack::pop() {
    if (!isEmpty()) {
        char popDigit = top->digit;
        Node *temp = top;
        
        top = top->next;
        --size;
        
        free(temp);
        
        return popDigit;
    }
    
    return NULL;
}

char Stack::peek() {
    if (!isEmpty()) {
        return top->digit;
    }
    
    return NULL;
}

bool Stack::isEmpty() {
    return size <= 0;
}

void Stack::freeMemory() {
    if (this->size > 0) {
        while (top != NULL) {
            Node *temp = top;
            
            top = top->next;
            --size;
            
            free(temp);
        }
    }
}

Stack stackcpy(Stack destination, const Stack source) {
    return destination;
}

std::ostream& operator<< (std::ostream& out, const Stack& stack) {
    char *digits = (char *) malloc(stack.size);
    Node *current = stack.top;
    
    if (current != NULL) {
        for (size_t i = stack.size; i > 0; i--) {
            digits[i - 1] = current->digit;
            current = current->next;
        }
        
        char *digitsWithoutLeadingZeros = (char *) malloc(stack.size);
        
        int i = 0;
        while (digits[i] == '0') {
            i++;
        }
        
        strncpy(digitsWithoutLeadingZeros, digits + i, stack.size - i);
        
        out << digitsWithoutLeadingZeros << std::endl;
        
        free(digitsWithoutLeadingZeros);
    }
    
    free(digits);
    
    return out;
}
