//PriorityQueue.h
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

    void enqueue(int value, int priority);
    void dequeue();
    std::pair<int, int> peek() const;
    bool isEmpty() const;

    // Display function to print the contents of the priority queue
    void print() const {
        if (heap.empty()) {
            std::cout << "Priority Queue is empty.\n";
            return;
        }
        std::cout << "Priority Queue contents:\n";
        for (const auto& item : heap) {
            std::cout << "Priority: " << item.first << ", Value: " << item.second << '\n';
        }
    }

    void draw(sf::RenderWindow& window);

    // File parsing
    void parseFromFile(const std::string& fileName);
};

#endif