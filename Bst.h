//BstFinal.h
#ifndef BST_H
#define BST_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <SFML/Graphics.hpp>

class BST {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;
        Node(int v) : value(v), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Helper functions
    Node* insertNode(Node* node, int value);
    Node* deleteNode(Node* node, int value);
    Node* findMin(Node* node);
    bool searchNode(Node* node, int value);
    void inorderTraversal(Node* node, std::ostream& os) const;
    void clearTree(Node* node);
    void printTree(Node* node, int space, int indent = 4) const; // Helper for print()

public:
    BST();
    ~BST();

    // Public interface
    void insert(int value);
    void deleteValue(int value);
    bool search(int value);
    void displayTree() const;
    void parseFromFile(const std::string& fileName);
    void draw(sf::RenderWindow& window);

    // New function
    void print() const;
};

#endif
