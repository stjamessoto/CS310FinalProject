#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <SFML/Graphics.hpp>

// Priority Queue class using a min-heap
class PriorityQueue {
private:
    std::vector<std::pair<int, int>> heap; // Pair: {priority, value}

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    PriorityQueue() = default;

    // Insert a value with a given priority (default is 0 for normal priority)
    void insert(int value, int priority = 0);

    // Remove the highest priority (lowest value) element
    void remove();

    // Peek at the element with the highest priority without removing it
    std::pair<int, int> peek() const;

    // Check if the priority queue is empty
    bool isEmpty() const;

    // Display function to print the contents of the priority queue
    void print() const;

    // Draw the priority queue (for SFML)
    void draw(sf::RenderWindow& window, const sf::Font& font);

    // Parse from file
    void parseFromFile(const std::string& fileName);

    // Getter for the internal heap data (returns the heap as a vector of pairs)
    std::vector<std::pair<int, int>> getData() const;

    // Getter for values (returns just the values from the heap)
    std::vector<int> getValues() const;

    // Getter for priorities (returns just the priorities from the heap)
    std::vector<int> getPriorities() const;

    // Check if the priority queue contains a value
    bool contains(int value) const;

    // Remove a specific value from the priority queue
    void deleteValue(int value);
};

#endif
