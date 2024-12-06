//Queue.cpp
#include <SFML/Graphics.hpp>
#include "Queue.h"

void Queue::enqueue(int value) {
    // Add an element to the back of the queue
    queue.push_back(value);
}

void Queue::dequeue() {
    // Remove the front element of the queue
    if (!isEmpty()) {
        queue.pop_front();
    }
}

int Queue::front() const {
    // Get the front element of the queue
    if (!isEmpty()) {
        return queue.front();
    }
    return -1; // Return an invalid value if the queue is empty
}

bool Queue::isEmpty() const {
    // Check if the queue is empty
    return queue.empty();
}

void Queue::display() const {
    // Display the elements of the queue
    if (queue.empty()) {
        std::cout << "Queue is empty!" << std::endl;
        return;
    }

    for (int value : queue) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

void Queue::draw(sf::RenderWindow& window) {
    // Draw the elements of the queue on the window
    float xPos = 50.0f;
    float yPos = 50.0f;
    float offset = 40.0f; // Spacing between elements

    for (int value : queue) {
        // Create a rectangle for each element in the queue
        sf::RectangleShape rectangle(sf::Vector2f(30.0f, 30.0f));
        rectangle.setPosition(xPos, yPos);
        rectangle.setFillColor(sf::Color::Green);

        // Create text to display the value inside the rectangle
        sf::Font font;
        if (!font.loadFromFile("edosz.ttf")) {  // Make sure you have the correct path to the font
            std::cerr << "Failed to load font!" << std::endl;
        }

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(value));
        text.setCharacterSize(15);
        text.setFillColor(sf::Color::Black);
        text.setPosition(xPos + 5, yPos + 5); // Position the text inside the rectangle

        // Draw the rectangle and text
        window.draw(rectangle);
        window.draw(text);

        xPos += offset;  // Move the position for the next element
    }
}