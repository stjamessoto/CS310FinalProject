//stack.cpp
#include "Stack.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// Push an element onto the stack
void Stack::push(int value) {
    stack.push_back(value);
}

// Pop the top element from the stack
void Stack::pop() {
    if (!stack.empty()) {
        stack.pop_back();
    } else {
        std::cerr << "Stack is empty! Cannot pop.\n";
    }
}

// Get the top element of the stack
int Stack::top() const {
    if (!stack.empty()) {
        return stack.back();
    } else {
        std::cerr << "Stack is empty! No top element.\n";
        return -1; // Error code, or you could throw an exception
    }
}

// Check if the stack is empty
bool Stack::isEmpty() const {
    return stack.empty();
}

// Display the elements of the stack (prints to console)
void Stack::display() const {
    if (stack.empty()) {
        std::cout << "Stack is empty.\n";
        return;
    }

    std::cout << "Stack elements: ";
    for (int value : stack) {
        std::cout << value << " ";
    }
    std::cout << "\n";
}

// Draw the stack elements in a window (using SFML)
void Stack::draw(sf::RenderWindow& window) {
    const float elementWidth = 50.f;
    const float elementHeight = 30.f;
    const float startX = 350.f;  // Start position for drawing the stack
    const float startY = 550.f;  // Y position for the top of the stack

    // Draw each element of the stack from top to bottom
    for (size_t i = 0; i < stack.size(); ++i) {
        // Calculate the y position for each stack element (top element first)
        float yPosition = startY - (i * (elementHeight + 5));

        // Create a rectangle shape for the stack element
        sf::RectangleShape rectangle(sf::Vector2f(elementWidth, elementHeight));
        rectangle.setFillColor(sf::Color::Green);
        rectangle.setPosition(startX, yPosition);

        // Draw the rectangle
        window.draw(rectangle);

        // Create text for the stack element
        sf::Font font;
        if (!font.loadFromFile("edosz.ttf")) {  // Ensure you have a font file
            std::cerr << "Failed to load font!\n";
        }
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(stack[stack.size() - i - 1])); // Get stack value
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        text.setPosition(startX + 15.f, yPosition + 5.f); // Adjust position for text

        // Draw the text
        window.draw(text);
    }
}

// Print the stack contents to the console
void Stack::print() const {
    std::cout << "Stack contents (top to bottom): ";
    if (stack.empty()) {
        std::cout << "The stack is empty.\n";
    } else {
        for (int i = stack.size() - 1; i >= 0; --i) {
            std::cout << stack[i] << " ";
        }
        std::cout << "\n";
    }
}