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

    BTreeNode(int t, bool isLeaf) : t(t), isLeaf(isLeaf) {}

    void traverse();
    bool search(int key);
    void insertNonFull(int key);
    void splitChild(int i, BTreeNode* y);
    void print();  // Print the keys in this node
    void deleteValue(int key);  // Delete a value from this node

    // Method to get data (keys) from the node
    std::vector<int> getData() const {
        return keys;
    }
};

class BTree {
private:
    BTreeNode* root;
    int t; // Minimum degree

    // Helper function for drawing nodes recursively (moved to .cpp file)
    void drawNode(sf::RenderWindow& window, BTreeNode* node, float x, float y, float offset, const sf::Font& font);
    void deleteValueFromNode(BTreeNode* node, int key);  // Helper function for deleting from nodes

public:
    BTree(int t);  // Constructor to initialize the BTree
    BTree();       // Default constructor to initialize an empty tree
    void traverse();
    bool search(int key);
    void insert(int key);
    void display();
    void parseFromFile(const std::string& filename);
    
    // Declaration of draw method (definition moved to .cpp file)
    void draw(sf::RenderWindow& window, const sf::Font& font);  
    void print(); // Print the entire tree
    void deleteValue(int key);  // Public method to delete a value

    // Get data (keys) from the root of the tree
    std::vector<int> getData() const {
        if (root) {
            return root->getData(); // Returns the keys from the root node
        }
        return {}; // Return an empty vector if the tree is empty
    }
};

#endif

