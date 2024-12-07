#ifndef REDBLACK_H
#define REDBLACK_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

enum Color { RED, BLACK };

// Red-Black Tree Node
struct RBNode {
    int data;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;

    RBNode(int value) : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    RBNode* root;
    RBNode* TNULL; // Sentinel node

    void initializeNULLNode(RBNode* node, RBNode* parent);
    void preOrderHelper(RBNode* node);
    void inOrderHelper(RBNode* node);
    void postOrderHelper(RBNode* node);
    RBNode* searchTreeHelper(RBNode* node, int key);
    void balanceInsert(RBNode* node);
    void balanceDelete(RBNode* node);
    void transplant(RBNode* u, RBNode* v);
    RBNode* minimum(RBNode* node);
    void deleteNodeHelper(RBNode* node, int key);

    // Rotation functions
    void leftRotate(RBNode* x);
    void rightRotate(RBNode* x);

    // Recursively delete all nodes
    void clear(RBNode* node);

    // Helper function to recursively draw the tree
    void drawNode(sf::RenderWindow& window, RBNode* node, float x, float y, const sf::Font& font);

public:
    RedBlackTree();
    ~RedBlackTree();

    void insert(int key);
    bool search(int key);
    void deleteValue(int key);
    void display();
    void print(); // New function to print the tree
    void parseFromFile(const std::string& filename);

    // Modified to accept window and font for drawing
    void draw(sf::RenderWindow& window, const sf::Font& font);
};

#endif // REDBLACK_H
