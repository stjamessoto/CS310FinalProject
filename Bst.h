//BstFinal.h
#ifndef BST_H
#define BST_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>  
#include <SFML/Graphics.hpp>

class BST {
protected:
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
    void inorderTraversal(Node* node, std::ostream& os) const;  // Existing for printing to ostream
    void inorderTraversal(Node* node, std::vector<int>& data) const;  // New helper for filling vector
    void clearTree(Node* node);
    void printTree(Node* node, int space, int indent = 4) const; // Helper for print()
    void drawNode(sf::RenderWindow& window, Node* node, float x, float y, float offset) const; // Helper for draw()

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

    Node* getRoot() const;  // Get the root node

    // Function to get data from the tree in the form of a vector
    std::vector<int> getData() const;   // New function to return data as a vector

    void print() const;
};

#endif
