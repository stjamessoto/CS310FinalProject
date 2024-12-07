//AVL.h
#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>

struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVL {
public:
    AVL();
    ~AVL();

    void insert(int key);
    void deleteValue(int key);
    bool search(int key) const;
    void parseFromFile(const std::string& fileName);
    void draw(sf::RenderWindow& window);
    void display() const;

    // New Methods
    void print() const; // Print method
    int getDepth(int key) const;
    int getOrder(int key) const;
    std::vector<int> getData() const;  // Ensure this returns a vector of int

private:
    AVLNode* root;

    AVLNode* insert(AVLNode* node, int key);
    AVLNode* deleteNode(AVLNode* node, int key);
    AVLNode* minValueNode(AVLNode* node);

    int getHeight(AVLNode* node) const;
    int getBalanceFactor(AVLNode* node) const;
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);

    void inOrderTraversal(AVLNode* node, std::vector<int>& keys) const;  // Updated to take a vector of keys
    void clear(AVLNode* node);

    // Helper functions for new methods
    int calculateDepth(AVLNode* node, int key, int depth) const;
    int calculateOrder(AVLNode* node, int key, int& order) const;

    void printInOrder(AVLNode* node) const; // Helper for the print method

    // Search helper function
    bool searchHelper(AVLNode* node, int key) const; // Added declaration
};

#endif // AVL_H
