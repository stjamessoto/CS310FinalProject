//Queue.cpp
#include "Queue.h"

void Queue::enqueue(int value) {
    queue.push_back(value);
    std::cout << "Enqueued " << value << " into the queue.\n";
}

void Queue::dequeue() {
    if (!queue.empty()) {
        std::cout << "Dequeued " << queue.front() << " from the queue.\n";
        queue.pop_front();
    } else {
        std::cerr << "Queue is empty. Cannot dequeue.\n";
    }
}

int Queue::front() const {
    if (!queue.empty()) {
        return queue.front();
    } else {
        throw std::out_of_range("Queue is empty.");
    }
}

bool Queue::isEmpty() const {
    return queue.empty();
}

void Queue::display() const {
    std::cout << "Queue contents (front to back): ";
    for (const int& value : queue) {
        std::cout << value << " ";
    }
    std::cout << "\n";
}
