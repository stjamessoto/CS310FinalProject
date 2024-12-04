//BstFinal.h
#ifndef BST_H
#define BST_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>

class BST {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;
        Node(int v) : value(v), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Helper functions
    Node* insertNode(Node* node, int value);
    Node* deleteNode(Node* node, int value);
    Node* findMin(Node* node);
    bool searchNode(Node* node, int value);
    void inorderTraversal(Node* node, std::ostream& os) const;
    void clearTree(Node* node);

public:
    BST();
    ~BST();

    // Public interface
    void insert(int value);
    void deleteValue(int value);
    bool search(int value);
    void displayTree() const;
    void parseFromFile(const std::string& fileName);
};

#endif
