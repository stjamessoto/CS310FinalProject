#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>

// Struct representing a single AVL tree node
struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

// AVL Tree class
class AVL {
public:
    // Constructor and Destructor
    AVL();
    ~AVL();

    // Core AVL Tree Operations
    void insert(int key);                          // Insert a key
    void deleteValue(int key);                     // Delete a key
    bool search(int key) const;                    // Search for a key
    bool contains(int key, int& depth, int& order) const;  // Check if key exists, return depth and order

    // Additional Operations
    void parseFromFile(const std::string& fileName);  // Load tree from a file
    void display() const;                             // Display tree in console
    void print() const;                               // Print method for debugging
    int getDepth(int key) const;                      // Get depth of a key in the tree
    int getOrder(int key) const;                      // Get in-order position of a key
    std::vector<int> getData() const;                 // Return all data in in-order traversal

    // Visualization
    void draw(sf::RenderWindow& window, const sf::Font& font);  // Draw the tree using SFML

private:
    AVLNode* root;

    // Internal Recursive Helper Functions
    AVLNode* insert(AVLNode* node, int key);                 // Recursive insert
    AVLNode* deleteNode(AVLNode* node, int key);              // Recursive delete
    AVLNode* minValueNode(AVLNode* node);                     // Find minimum node
    int getHeight(AVLNode* node) const;                       // Get the height of a node
    int getBalanceFactor(AVLNode* node) const;                // Get the balance factor of a node

    // Balance function for AVL tree
    AVLNode* balance(AVLNode* node);                          // Balance the tree

    // Rotations for Balancing
    AVLNode* rotateRight(AVLNode* y);                         // Perform right rotation
    AVLNode* rotateLeft(AVLNode* x);                          // Perform left rotation

    // Traversal Helpers
    void inOrderTraversal(AVLNode* node, std::vector<int>& keys) const;  // In-order traversal
    void clear(AVLNode* node);                                  // Clear the tree
    void printInOrder(AVLNode* node) const;                      // Print nodes in in-order

    // Helper Functions for New Features
    int calculateDepth(AVLNode* node, int key, int depth) const;  // Calculate the depth of a key
    int calculateOrder(AVLNode* node, int key, int& order) const; // Calculate in-order position of a key
    bool searchHelper(AVLNode* node, int key) const;              // Recursive helper for search

    // Visualization Helper
    void drawNode(sf::RenderWindow& window, AVLNode* node, const sf::Font& font,
                  float x, float y, float xOffset) const;            // Draw a node using SFML
};

#endif // AVL_H
