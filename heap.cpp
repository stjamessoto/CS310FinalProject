#include "Heap.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Constructor
Heap::Heap() {}

// Heapify up to maintain heap property during insertion
void Heap::heapifyUp(int index) {
    if (index <= 0) return;

    int parent = (index - 1) / 2;
    if (heap[parent] < heap[index]) {
        std::swap(heap[parent], heap[index]);
        heapifyUp(parent);
    }
}

// Heapify down to maintain heap property during deletion
void Heap::heapifyDown(int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int largest = index;

    if (leftChild < heap.size() && heap[leftChild] > heap[largest])
        largest = leftChild;

    if (rightChild < heap.size() && heap[rightChild] > heap[largest])
        largest = rightChild;

    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}

// Insert a value into the heap
void Heap::insert(int value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1); // Restore heap property
}

// Delete a specific value from the heap
void Heap::deleteValue(int value) {
    auto it = std::find(heap.begin(), heap.end(), value);
    if (it != heap.end()) {
        int index = std::distance(heap.begin(), it);
        std::swap(heap[index], heap.back()); // Swap with last element
        heap.pop_back();
        heapifyDown(index); // Restore heap property
    }
}

// Search for a value in the heap
bool Heap::search(int value) {
    return std::find(heap.begin(), heap.end(), value) != heap.end();
}

// Populate heap from a file
void Heap::parseFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << fileName << "\n";
        return;
    }

    int value;
    while (file >> value) {
        insert(value);
    }
    file.close();
}

// Display the heap contents
void Heap::displayHeap() {
    for (int value : heap) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

// Function to visualize the heap using SFML
void Heap::draw(sf::RenderWindow& window) {
    if (heap.empty()) return;

    // Set up parameters for the visualization
    float xOffset = 400.f;   // Initial horizontal position
    float yOffset = 50.f;    // Initial vertical position
    float offset = 200.f;    // Horizontal space between nodes at each level

    // Create a circle for each node and draw lines to children
    for (size_t i = 0; i < heap.size(); ++i) {
        float x = xOffset + (i % 2) * offset;
        float y = yOffset + (i / 2) * 50;

        // Draw the node
        sf::CircleShape circle(30);  // Create a circle with radius 30
        circle.setFillColor(sf::Color::Green);
        circle.setPosition(x, y);

        sf::Text text;
        text.setString(std::to_string(heap[i]));
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(24);
        text.setPosition(x + 10, y + 5); // Adjust position for text inside the circle

        window.draw(circle);
        window.draw(text);

        // Draw lines to the children
        int leftChildIndex = 2 * i + 1;
        int rightChildIndex = 2 * i + 2;
        if (leftChildIndex < heap.size()) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x + 30, y + 30)),
                sf::Vertex(sf::Vector2f(xOffset + leftChildIndex % 2 * offset + 30, yOffset + (leftChildIndex / 2) * 50 + 30))
            };
            window.draw(line, 2, sf::Lines);
        }

        if (rightChildIndex < heap.size()) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x + 30, y + 30)),
                sf::Vertex(sf::Vector2f(xOffset + rightChildIndex % 2 * offset + 30, yOffset + (rightChildIndex / 2) * 50 + 30))
            };
            window.draw(line, 2, sf::Lines);
        }
    }
}

// Print the heap state to the console
void Heap::print() const {
    std::cout << "Heap contents: ";
    for (int val : heap) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}