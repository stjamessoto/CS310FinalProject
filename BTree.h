//BTree.h
#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>

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

public:
    BTree(int t);
    void traverse();
    bool search(int key);
    void insert(int key);
    void display();
    void parseFromFile(const std::string& filename);
};

#endif
