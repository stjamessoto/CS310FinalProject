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
    void insert(int key);
    void deleteValue(int key);
    bool search(int key) const;

    // Additional Operations
    void parseFromFile(const std::string& fileName);  // Load tree from a file
    void display() const;                             // Display tree in console
    void print() const;                               // Print method for debugging
    int getDepth(int key) const;                      // Get depth of a key in the tree
    int getOrder(int key) const;                      // Get in-order position of a key
    std::vector<int> getData() const;                 // Return all data in in-order traversal

    // Visualization
    void draw(sf::RenderWindow& window, const sf::Font& font);  // Updated to include sf::Font

private:
    AVLNode* root;

    // Internal Recursive Helper Functions
    AVLNode* insert(AVLNode* node, int key);
    AVLNode* deleteNode(AVLNode* node, int key);
    AVLNode* minValueNode(AVLNode* node);
    int getHeight(AVLNode* node) const;
    int getBalanceFactor(AVLNode* node) const;

    // Balance function for AVL tree
    AVLNode* balance(AVLNode* node);  // Added balance function declaration

    // Rotations for Balancing
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);

    // Traversal Helpers
    void inOrderTraversal(AVLNode* node, std::vector<int>& keys) const;
    void clear(AVLNode* node);
    void printInOrder(AVLNode* node) const;

    // Helper Functions for New Features
    int calculateDepth(AVLNode* node, int key, int depth) const;
    int calculateOrder(AVLNode* node, int key, int& order) const;
    bool searchHelper(AVLNode* node, int key) const;

    // Visualization Helper
    void drawNode(sf::RenderWindow& window, AVLNode* node, const sf::Font& font,
                  float x, float y, float xOffset) const;
};

#endif // AVL_H
