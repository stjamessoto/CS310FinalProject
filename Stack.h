//stack.h
#ifndef STACK_H
#define STACK_H

#include <vector>
#include <iostream>

class Stack {
private:
    std::vector<int> stack;

public:
    void push(int value);   // Add an element to the stack
    void pop();             // Remove the top element
    int top() const;        // Get the top element
    bool isEmpty() const;   // Check if the stack is empty
    void display() const;   // Display the stack
};

#endif // STACK_H