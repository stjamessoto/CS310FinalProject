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
    Node* insertNode(Node* node, int value);  // Insert node recursively
    Node* deleteNode(Node* node, int value);  // Delete node recursively
    Node* findMin(Node* node);                // Find the minimum node
    bool searchNode(Node* node, int value);   // Search helper function
    void inorderTraversal(Node* node, std::ostream& os) const;  // For printing to ostream
    void inorderTraversal(Node* node, std::vector<int>& data) const;  // For filling vector
    void clearTree(Node* node);  // Clear tree recursively
    void printTree(Node* node, int space, int indent = 4) const;  // For printing tree structure
    void drawNode(sf::RenderWindow& window, Node* node, float x, float y, float offset) const; // Helper for draw()

public:
    BST();   // Constructor
    ~BST();  // Destructor

    // Public interface
    void insert(int value);        // Public insert method
    void deleteValue(int value);  // Public delete method (calls deleteNode)
    bool search(int value);       // Public search method (search equivalent)
    bool contains(int value);     // New contains method (checks if value exists)
    void displayTree() const;     // Display tree structure in console
    void parseFromFile(const std::string& fileName);  // Parse data from file
    void draw(sf::RenderWindow& window, const sf::Font& font); // Draw tree to window

    Node* getRoot() const;        // Get the root node

    // Function to get data from the tree in the form of a vector
    std::vector<int> getData() const;   // New function to return data as a vector

    void print() const;  // Print tree to console
};

#endif
