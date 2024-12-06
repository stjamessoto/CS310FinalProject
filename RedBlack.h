// RedBlack.h
#ifndef REDBLACK_H
#define REDBLACK_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

enum Color { RED, BLACK };

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

    // Add declarations for rotations
    void leftRotate(RBNode* x);
    void rightRotate(RBNode* x);

public:
    RedBlackTree();
    ~RedBlackTree();

    void insert(int key);
    bool search(int key);
    void deleteValue(int key);
    void display();
    void parseFromFile(const std::string& filename);
    void draw(sf::RenderWindow& window);
};

#endif // REDBLACK_H
