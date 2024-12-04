//PriorityQueue.cpp
#include "PriorityQueue.h"
#include <fstream>
#include <sstream>
#include <iomanip>

// Helper function: Swap two heap elements
void PriorityQueue::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent].first <= heap[index].first) break;
        std::swap(heap[parent], heap[index]);
        index = parent;
    }
}

void PriorityQueue::heapifyDown(int index) {
    int size = heap.size();
    while (index < size) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && heap[left].first < heap[smallest].first)
            smallest = left;
        if (right < size && heap[right].first < heap[smallest].first)
            smallest = right;

        if (smallest == index) break;

        std::swap(heap[index], heap[smallest]);
        index = smallest;
    }
}

// Enqueue with priority
void PriorityQueue::enqueue(int value, int priority) {
    heap.emplace_back(priority, value);
    heapifyUp(heap.size() - 1);
}

// Dequeue the highest-priority (lowest-priority-number) element
void PriorityQueue::dequeue() {
    if (heap.empty()) throw std::runtime_error("PriorityQueue is empty");
    std::swap(heap.front(), heap.back());
    heap.pop_back();
    if (!heap.empty()) heapifyDown(0);
}

// Peek at the highest-priority element
std::pair<int, int> PriorityQueue::peek() const {
    if (heap.empty()) throw std::runtime_error("PriorityQueue is empty");
    return heap.front();
}

// Check if the priority queue is empty
bool PriorityQueue::isEmpty() const {
    return heap.empty();
}

// Display the priority queue
void PriorityQueue::display() const {
    std::cout << "Priority Queue:\n";
    std::cout << std::setw(10) << "Priority" << std::setw(10) << "Value\n";
    for (const auto& [priority, value] : heap) {
        std::cout << std::setw(10) << priority << std::setw(10) << value << '\n';
    }
}

// Parse values and priorities from a file
void PriorityQueue::parseFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << '\n';
        return;
    }

    int value, priority;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (iss >> value >> priority) {
            enqueue(value, priority);
        } else {
            std::cerr << "Invalid line in file: " << line << '\n';
        }
    }

    file.close();
}
