//BTree.h
#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>

class BTreeNode {
public:
    std::vector<int> keys;
    std::vector<BTreeNode*> children;
    bool isLeaf;
    int t; // Minimum degree

    BTreeNode(int t, bool isLeaf);

    void traverse();
    bool search(int key);
    void insertNonFull(int key);
    void splitChild(int i, BTreeNode* y);
    void print();  // Print the keys in this node
    void deleteValue(int key);  // Delete a value from this node
};

class BTree {
private:
    BTreeNode* root;
    int t; // Minimum degree

    // Helper function for drawing nodes recursively
    void drawNode(sf::RenderWindow& window, BTreeNode* node, float x, float y, float offset);
    void deleteValueFromNode(BTreeNode* node, int key);  // Helper function for deleting from nodes

public:
    BTree(int t);
    void traverse();
    bool search(int key);
    void insert(int key);
    void display();
    void parseFromFile(const std::string& filename);
    void draw(sf::RenderWindow& window);
    void print(); // Print the entire tree
    void deleteValue(int key);  // Public method to delete a value
};

#endif

