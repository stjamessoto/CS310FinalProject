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
};

class BTree {
private:
    BTreeNode* root;
    int t; // Minimum degree

    // Helper function for drawing nodes recursively
    void drawNode(sf::RenderWindow& window, BTreeNode* node, float x, float y, float offset);

public:
    BTree(int t);
    void traverse();
    bool search(int key);
    void insert(int key);
    void display();
    void parseFromFile(const std::string& filename);
    void draw(sf::RenderWindow& window);
};

#endif
