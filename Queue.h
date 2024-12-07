#ifndef QUEUE_H
#define QUEUE_H

#include <deque>
#include <vector>
#include <SFML/Graphics.hpp>
#include <algorithm>  

class Queue {
private:
    std::deque<int> queue;

public:
    // Add an element to the queue
    void enqueue(int value);

    // Remove an element from the front of the queue
    void dequeue();

    // Get the front element of the queue
    int front() const;

    // Check if the queue is empty
    bool isEmpty() const;

    // Display the queue in the console (as a simple text output)
    void display() const;

    // Draw the queue visually on the screen using SFML
    void draw(sf::RenderWindow& window, const sf::Font& font);

    // Print the queue elements in the console
    void print() const;

    // Return the queue elements as a vector
    std::vector<int> getElements() const;

    // Check if a value is in the queue
    bool contains(int value) const;
};

#endif // QUEUE_H
