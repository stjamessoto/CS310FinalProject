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
    // Add an element to the stack
    void push(int value);

    // Remove the top element
    void pop();

    // Get the top element
    int top() const;

    // Check if the stack is empty
    bool isEmpty() const;

    // Display the stack (using SFML rendering)
    void display() const;

    // SFML-specific draw function, added font parameter
    void draw(sf::RenderWindow& window, const sf::Font& font);

    // Print the stack contents to the console
    void print() const;

    // Return all elements of the stack
    std::vector<int> getElements() const;
};

#endif // STACK_H
