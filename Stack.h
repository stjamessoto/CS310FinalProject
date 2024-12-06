//stack.h
#ifndef STACK_H
#define STACK_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class Stack {
private:
    std::vector<int> stack;

public:
    void push(int value);   // Add an element to the stack
    void pop();             // Remove the top element
    int top() const;        // Get the top element
    bool isEmpty() const;   // Check if the stack is empty
    void display() const;   // Display the stack
    void draw(sf::RenderWindow& window);
};

#endif // STACK_H