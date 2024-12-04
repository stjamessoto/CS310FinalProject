//Queue.h
#ifndef QUEUE_H
#define QUEUE_H

#include <deque>
#include <iostream>

class Queue {
private:
    std::deque<int> queue;

public:
    void enqueue(int value); // Add an element to the queue
    void dequeue();          // Remove an element from the front
    int front() const;       // Get the front element
    bool isEmpty() const;    // Check if the queue is empty
    void display() const;    // Display the queue
};

#endif // QUEUE_H