//stack.cpp
#include "Stack.h"

void Stack::push(int value) {
    stack.push_back(value);
    std::cout << "Pushed " << value << " onto the stack.\n";
}

void Stack::pop() {
    if (!stack.empty()) {
        std::cout << "Popped " << stack.back() << " from the stack.\n";
        stack.pop_back();
    } else {
        std::cerr << "Stack is empty. Cannot pop.\n";
    }
}

int Stack::top() const {
    if (!stack.empty()) {
        return stack.back();
    } else {
        throw std::out_of_range("Stack is empty.");
    }
}

bool Stack::isEmpty() const {
    return stack.empty();
}

void Stack::display() const {
    std::cout << "Stack contents (top to bottom): ";
    for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}