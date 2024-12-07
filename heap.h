// heap.h
#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

class Heap {
private:
    std::vector<int> heap; // Vector to store heap elements

    void heapifyUp(int index);   // Maintain heap property during insertion
    void heapifyDown(int index); // Maintain heap property during deletion

public:
    Heap();                      // Constructor
    void insert(int value);      // Insert a value into the heap
    void deleteValue(int value); // Delete a specific value from the heap
    bool search(int value);      // Search for a value in the heap
    void parseFromFile(const std::string& fileName); // Populate heap from a file
    void buildHeap(const std::vector<int>& data);  // Build the heap from a given data array
    void displayHeap();          // Display the heap contents
    void draw(sf::RenderWindow& window, const sf::Font& font);  // Draw the heap visually

    // Print the current heap state to the console
    void print() const;

    // Getter method to access heap data (only declare, no definition here)
    std::vector<int> getData() const;
};

#endif
