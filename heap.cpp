#include "heap.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Heap::Heap() {}

// Insert a value into the heap
void Heap::insert(int value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
    std::cout << "Inserted value: " << value << "\n";
}

// Delete a specific value from the heap
void Heap::deleteValue(int value) {
    auto it = std::find(heap.begin(), heap.end(), value);
    if (it != heap.end()) {
        int index = it - heap.begin();
        std::swap(heap[index], heap.back());
        heap.pop_back();
        heapifyDown(index);
        std::cout << "Deleted value: " << value << "\n";
    } else {
        std::cout << "Value not found in the heap.\n";
    }
}

// Search for a value in the heap
bool Heap::search(int value) {
    return std::find(heap.begin(), heap.end(), value) != heap.end();
}

// Maintain heap property during insertion
void Heap::heapifyUp(int index) {
    while (index > 0 && heap[index] > heap[(index - 1) / 2]) {
        std::swap(heap[index], heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

// Maintain heap property during deletion
void Heap::heapifyDown(int index) {
    int size = heap.size();
    while (index < size) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;

        if (leftChild < size && heap[leftChild] > heap[largest]) {
            largest = leftChild;
        }
        if (rightChild < size && heap[rightChild] > heap[largest]) {
            largest = rightChild;
        }
        if (largest != index) {
            std::swap(heap[index], heap[largest]);
            index = largest;
        } else {
            break;
        }
    }
}

// Populate heap from a file
void Heap::parseFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Error: Unable to open file " << fileName << "\n";
        return;
    }

    int value;
    while (file >> value) {
        insert(value);
    }

    file.close();
    std::cout << "Heap populated from file: " << fileName << "\n";
}

// Display the heap contents
void Heap::displayHeap() {
    std::cout << "Heap contents: ";
    for (int value : heap) {
        std::cout << value << " ";
    }
    std::cout << "\n";
}