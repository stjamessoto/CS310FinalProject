#include "Queue.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm> 

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

    std::cout << "Queue: ";
    for (int value : queue) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

void Queue::draw(sf::RenderWindow& window, const sf::Font& font) {
    // Draw the elements of the queue on the window
    float xPos = 100.0f;  // Starting position for drawing elements
    float yPos = 250.0f;  // Y position for the first element
    float offset = 60.0f; // Spacing between elements

    // Iterate through each element in the queue and display it
    for (size_t i = 0; i < queue.size(); ++i) {
        // Create a rectangle for each element in the queue
        sf::RectangleShape rectangle(sf::Vector2f(50.0f, 50.0f));  // Adjusted size for better readability
        rectangle.setPosition(xPos + (i * offset), yPos);
        rectangle.setFillColor(sf::Color::Green);

        // Create text to display the value inside the rectangle
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(queue[i]));
        text.setCharacterSize(20);  // Adjust text size for better readability
        text.setFillColor(sf::Color::Black);
        text.setPosition(xPos + (i * offset) + 10, yPos + 10); // Center text inside rectangle

        // Draw the rectangle and the text
        window.draw(rectangle);
        window.draw(text);
    }
}

std::vector<int> Queue::getElements() const {
    // Convert deque to vector and return
    return std::vector<int>(queue.begin(), queue.end());
}

bool Queue::contains(int value) const {
    // Use std::find to check if value is in the deque
    return std::find(queue.begin(), queue.end(), value) != queue.end();
}
