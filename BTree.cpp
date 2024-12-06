//BTree.cpp
#include "BTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>

// BTreeNode Constructor
BTreeNode::BTreeNode(int t, bool isLeaf) {
    this->t = t;
    this->isLeaf = isLeaf;
}

// Traverse the BTreeNode
void BTreeNode::traverse() {
    for (size_t i = 0; i < keys.size(); ++i) {
        if (!isLeaf) {
            children[i]->traverse();
        }
        std::cout << keys[i] << " ";
    }
    if (!isLeaf) {
        children[keys.size()]->traverse();
    }
}

// Print the keys of the current node
void BTreeNode::print() {
    for (int key : keys) {
        std::cout << key << " ";
    }
    std::cout << std::endl;
}

// Search a key in this node
bool BTreeNode::search(int key) {
    int i = 0;
    while (i < keys.size() && key > keys[i]) {
        i++;
    }
    if (i < keys.size() && keys[i] == key) {
        return true;
    }
    if (isLeaf) {
        return false;
    }
    return children[i]->search(key);
}

// Insert key into non-full node
void BTreeNode::insertNonFull(int key) {
    int i = keys.size() - 1;
    if (isLeaf) {
        // Find the correct position for the new key
        while (i >= 0 && keys[i] > key) {
            i--;
        }
        keys.insert(keys.begin() + i + 1, key);
    } else {
        // Find the child to insert into
        while (i >= 0 && keys[i] > key) {
            i--;
        }
        i++;

        // If the child is full, split it
        if (children[i]->keys.size() == 2 * t - 1) {
            splitChild(i, children[i]);
            if (key > keys[i]) {
                i++;
            }
        }
        children[i]->insertNonFull(key);
    }
}

// Split the child node
void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->isLeaf);
    z->keys = std::vector<int>(y->keys.begin() + t, y->keys.end());
    y->keys.resize(t - 1);

    if (!y->isLeaf) {
        z->children = std::vector<BTreeNode*>(y->children.begin() + t, y->children.end());
        y->children.resize(t);
    }

    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
}

// BTree Constructor
BTree::BTree(int t) {
    this->t = t;
    root = new BTreeNode(t, true);
}

// Traverse the tree
void BTree::traverse() {
    if (root != nullptr) {
        root->traverse();
    }
}

// Print the entire tree (in-order traversal)
void BTree::print() {
    if (root != nullptr) {
        root->print();
    }
}

// Search for a key in the BTree
bool BTree::search(int key) {
    return root->search(key);
}

// Insert a key into the BTree
void BTree::insert(int key) {
    if (root->keys.size() == 2 * t - 1) {
        BTreeNode* s = new BTreeNode(t, false);
        s->children.push_back(root);
        s->splitChild(0, root);

        int i = 0;
        if (s->keys[0] < key) {
            i++;
        }
        s->children[i]->insertNonFull(key);
        root = s;
    } else {
        root->insertNonFull(key);
    }
}

// Display the tree (in-order traversal)
void BTree::display() {
    traverse();
    std::cout << std::endl;
}

// Parse data from a file and insert into the BTree
void BTree::parseFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    int key;
    while (file >> key) {
        insert(key);
    }
    file.close();
}

// Helper function to draw the BTreeNode
void BTree::drawNode(sf::RenderWindow& window, BTreeNode* node, float x, float y, float offset) {
    if (!node) return;

    // Draw the node (keys)
    sf::CircleShape nodeShape(30);
    nodeShape.setFillColor(sf::Color::Green);
    nodeShape.setPosition(x, y);
    window.draw(nodeShape);

    sf::Text text;
    text.setFont(sf::Font());
    text.setString(std::to_string(node->keys[0]));
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x + 10, y + 10);
    window.draw(text);

    // Recursively draw children nodes
    float childOffset = offset / 2;
    for (size_t i = 0; i < node->children.size(); ++i) {
        float childX = x + (i - (node->children.size() / 2)) * 100;
        float childY = y + 80;
        drawNode(window, node->children[i], childX, childY, childOffset);
    }
}

// Draw the BTree using SFML
void BTree::draw(sf::RenderWindow& window) {
    if (root != nullptr) {
        drawNode(window, root, 400, 50, 200);
    }
}

// Public method to delete a value from the tree
void BTree::deleteValue(int key) {
    deleteValueFromNode(root, key);
}

// Helper function to delete a value from a node
void BTree::deleteValueFromNode(BTreeNode* node, int key) {
    int i = 0;
    while (i < node->keys.size() && node->keys[i] < key) {
        i++;
    }

    if (i < node->keys.size() && node->keys[i] == key) {
        if (node->isLeaf) {
            node->keys.erase(node->keys.begin() + i);
        } else {
            // Handle internal node deletion (complex logic needed)
        }
    } else if (!node->isLeaf) {
        deleteValueFromNode(node->children[i], key);
    }
}




