#ifndef REDBLACK_H
#define REDBLACK_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>  // Include SFML for graphics

// Enum to define colors of Red-Black Tree nodes
enum Color { RED, BLACK };

// Red-Black Tree Node structure
struct RBNode {
    int data;          // The data stored in the node
    Color color;       // Color of the node (RED or BLACK)
    RBNode* left;      // Left child pointer
    RBNode* right;     // Right child pointer
    RBNode* parent;    // Parent pointer

    // Constructor to initialize a new node
    RBNode(int value) : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    RBNode* root;    // Root node of the tree
    RBNode* TNULL;   // Sentinel node representing leaf nodes (NULL)

    // Helper functions for balancing the tree and performing rotations
    void initializeNULLNode(RBNode* node, RBNode* parent);
    void preOrderHelper(RBNode* node);
    void inOrderHelper(RBNode* node);
    void postOrderHelper(RBNode* node);
    RBNode* searchTreeHelper(RBNode* node, int key);
    void balanceInsert(RBNode* node);  // Balances the tree after insertion
    void balanceDelete(RBNode* node);  // Balances the tree after deletion
    void transplant(RBNode* u, RBNode* v);
    RBNode* minimum(RBNode* node);
    void deleteNodeHelper(RBNode* node, int key);

    // Rotation functions to maintain the Red-Black Tree properties
    void leftRotate(RBNode* x);
    void rightRotate(RBNode* x);

    // Recursive cleanup function for deleting nodes
    void clear(RBNode* node);

    // Function to draw nodes of the tree in SFML
    void drawNode(sf::RenderWindow& window, RBNode* node, float x, float y, const sf::Font& font);

public:
    RedBlackTree();   // Constructor
    ~RedBlackTree();  // Destructor

    // Insertion and Deletion functions
    void insert(int key);
    void deleteValue(int key);

    // Search function
    bool search(int key);  // Search for a node with a specific key
    bool contains(int key);  // Check if a key exists in the tree

    // Display and Printing functions
    void display();
    void print();  // Print the tree (in-order traversal)

    // File parsing function
    void parseFromFile(const std::string& filename);

    // Function to draw the tree using SFML window and font for visualization
    void draw(sf::RenderWindow& window, const sf::Font& font);
};

#endif // REDBLACK_H
