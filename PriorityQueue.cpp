#include "PriorityQueue.h" 
#include <fstream>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <algorithm>  // For std::find_if

// Helper function to maintain the heap property after adding an element (heapify upwards)
void PriorityQueue::heapifyUp(int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (heap[index].first >= heap[parentIndex].first) break; // No need to swap
        std::swap(heap[index], heap[parentIndex]);
        index = parentIndex;
    }
}

// Helper function to maintain the heap property after removing the root (heapify downwards)
void PriorityQueue::heapifyDown(int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int smallest = index;

    if (leftChild < heap.size() && heap[leftChild].first < heap[smallest].first) {
        smallest = leftChild;
    }
    if (rightChild < heap.size() && heap[rightChild].first < heap[smallest].first) {
        smallest = rightChild;
    }

    if (smallest != index) {
        std::swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

// Insert an element with a priority
void PriorityQueue::insert(int value, int priority) {
    heap.push_back({priority, value});
    heapifyUp(heap.size() - 1);
}

// Remove the root element (remove the element with the highest priority)
void PriorityQueue::remove() {
    if (isEmpty()) {
        std::cerr << "Priority Queue is empty, cannot remove!" << std::endl;
        return;
    }

    // Swap the root with the last element, then remove the last element
    std::swap(heap[0], heap[heap.size() - 1]);
    heap.pop_back();
    heapifyDown(0); // Restore heap property
}

// Peek at the root element (the element with the highest priority)
std::pair<int, int> PriorityQueue::peek() const {
    if (isEmpty()) {
        std::cerr << "Priority Queue is empty, cannot peek!" << std::endl;
        throw std::out_of_range("Priority Queue is empty");
    }
    return heap[0];
}

// Check if the priority queue is empty
bool PriorityQueue::isEmpty() const {
    return heap.empty();
}

// Print the queue (for debugging purposes)
void PriorityQueue::print() const {
    if (heap.empty()) {
        std::cout << "Priority Queue is empty.\n";
        return;
    }
    std::cout << "Priority Queue contents:\n";
    for (const auto& item : heap) {
        std::cout << "Priority: " << item.first << ", Value: " << item.second << '\n';
    }
}

// Draw the priority queue using SFML
void PriorityQueue::draw(sf::RenderWindow& window, const sf::Font& font) {
    if (heap.empty()) return;

    float width = 50.0f;
    float height = 40.0f;
    float offsetX = 100.0f;
    float offsetY = 100.0f;
    float levelSpacing = 80.0f;

    // Traverse the heap and draw each node as a rectangle
    for (size_t i = 0; i < heap.size(); ++i) {
        float x = offsetX + (i % 2) * width; // Adjust x position for levels
        float y = offsetY + (i / 2) * levelSpacing; // Adjust y position for tree levels

        // Draw node as a rectangle
        sf::RectangleShape node(sf::Vector2f(width, height));
        node.setPosition(x, y);
        node.setFillColor(sf::Color::Green);

        // Draw the priority value inside the rectangle
        sf::Text text(std::to_string(heap[i].first), font, 20);
        text.setFillColor(sf::Color::White);
        text.setPosition(x + width / 4, y + height / 4);
       
        // Draw the node and the text
        window.draw(node);
        window.draw(text);
    }

    // Optionally, connect nodes to indicate relationships
    for (size_t i = 0; i < heap.size(); ++i) {
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;

        if (leftChild < heap.size()) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(offsetX + (i % 2) * width + width / 2, offsetY + (i / 2) * levelSpacing + height / 2)),
                sf::Vertex(sf::Vector2f(offsetX + (leftChild % 2) * width + width / 2, offsetY + (leftChild / 2) * levelSpacing + height / 2))
            };
            window.draw(line, 2, sf::Lines);
        }

        if (rightChild < heap.size()) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(offsetX + (i % 2) * width + width / 2, offsetY + (i / 2) * levelSpacing + height / 2)),
                sf::Vertex(sf::Vector2f(offsetX + (rightChild % 2) * width + width / 2, offsetY + (rightChild / 2) * levelSpacing + height / 2))
            };
            window.draw(line, 2, sf::Lines);
        }
    }
}

// Parse data from a file and populate the priority queue
void PriorityQueue::parseFromFile(const std::string& filename) {
    // Open the file
    std::ifstream file(filename);
    
    // Check if the file is open
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // Temporary variables to hold values and priorities
    int value, priority;

    // Read the file line by line
    while (file >> value >> priority) {
        // Insert the value with the specified priority
        insert(value, priority);
    }

    // Close the file
    file.close();

    // Inform the user that the file has been parsed successfully
    std::cout << "File parsed successfully: " << filename << std::endl;
}

// Get the internal data of the heap
std::vector<std::pair<int, int>> PriorityQueue::getData() const {
    return heap;
}

// Extract values from the pairs and return as a vector of ints
std::vector<int> PriorityQueue::getValues() const {
    std::vector<int> values;
    for (const auto& item : heap) {
        values.push_back(item.second);  // 'second' is the value part of the pair
    }
    return values;
}

// Extract priorities from the pairs and return as a vector of ints
std::vector<int> PriorityQueue::getPriorities() const {
    std::vector<int> priorities;
    for (const auto& item : heap) {
        priorities.push_back(item.first);  // 'first' is the priority part of the pair
    }
    return priorities;
}

// Check if the priority queue contains a specific value
bool PriorityQueue::contains(int value) const {
    for (const auto& pair : heap) {
        if (pair.second == value) {
            return true; // Found the value
        }
    }
    return false; // Value not found
}

// Remove a specific value from the priority queue
void PriorityQueue::deleteValue(int value) {
    // Find the element by its value
    auto it = std::find_if(heap.begin(), heap.end(), [value](const std::pair<int, int>& pair) {
        return pair.second == value;
    });

    // If the element is not found, do nothing
    if (it == heap.end()) {
        std::cerr << "Value not found in the priority queue" << std::endl;
        return;
    }

    // Get the index of the element to remove
    int index = std::distance(heap.begin(), it);

    // Swap the found element with the last element
    std::swap(heap[index], heap.back());

    // Remove the last element
    heap.pop_back();

    // Rebalance the heap
    heapifyDown(index);
    heapifyUp(index);
}
