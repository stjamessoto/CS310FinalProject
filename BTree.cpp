#include "BTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>

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
        keys.insert(keys.begin() + i + 1, key);  // Insert key correctly into keys vector
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
        children[i]->insertNonFull(key);  // Recurse into the child
    }
}

// Split the child node
void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->isLeaf);
    z->keys = std::vector<int>(y->keys.begin() + t, y->keys.end());  // Ensure keys is initialized as a vector
    y->keys.resize(t - 1);  // Resize the parent's keys after splitting

    if (!y->isLeaf) {
        z->children = std::vector<BTreeNode*>(y->children.begin() + t, y->children.end());  // Initialize children properly
        y->children.resize(t);  // Resize the parent's children after splitting
    }

    children.insert(children.begin() + i + 1, z);  // Insert the new child into the children vector
    keys.insert(keys.begin() + i, y->keys[t - 1]);  // Insert the middle key into the parent's keys
}

// BTree Constructor
BTree::BTree(int t) {
    this->t = t;
    root = new BTreeNode(t, true);  // Create the root node with a minimum degree t
}

// BTree Default Constructor
BTree::BTree() {
    this->t = 2;  // default minimum degree
    root = new BTreeNode(t, true); // Initialize root with a leaf node
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
    if (root != nullptr) {
        return root->search(key);
    }
    return false; // Return false if the tree is empty
}

// Contains method (checks if the tree contains the given key)
bool BTree::contains(int key) {
    if (root != nullptr) {
        return root->search(key);  // Simply reuse the search method
    }
    return false; // Return false if the tree is empty
}

// Insert a key into the BTree
void BTree::insert(int key) {
    if (root->keys.size() == 2 * t - 1) {  // If the root is full
        BTreeNode* s = new BTreeNode(t, false);
        s->children.push_back(root);
        s->splitChild(0, root);

        int i = 0;
        if (s->keys[0] < key) {
            i++;
        }
        s->children[i]->insertNonFull(key);  // Insert into the appropriate child
        root = s;  // New root is the split node
    } else {
        root->insertNonFull(key);  // Insert into the non-full root
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
        insert(key);  // Insert each key read from the file
    }
    file.close();
}

// Helper function to draw the BTreeNode using rectangles
void BTree::drawNode(sf::RenderWindow& window, BTreeNode* node, float x, float y, float offset, const sf::Font& font) {
    if (!node) return;

    // Draw the node (rectangular shape for each node)
    sf::RectangleShape nodeShape(sf::Vector2f(60, 50));  // Rectangle shape with width and height
    nodeShape.setFillColor(sf::Color::Green);
    nodeShape.setPosition(x - 30, y - 25);  // Center the rectangle on (x, y)
    window.draw(nodeShape);

    // Draw the keys in the node
    for (size_t i = 0; i < node->keys.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(node->keys[i]));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        text.setPosition(x - 10 + i * 20, y - 10);  // Center the text inside the rectangle
        window.draw(text);
    }

    // Recursively draw children nodes
    if (!node->isLeaf) {
        float childOffset = offset / 2;
        for (size_t i = 0; i < node->children.size(); ++i) {
            float childX = x + (i - (node->children.size() / 2)) * 100;  // Space children evenly
            float childY = y + 80;  // Draw children below their parent
            // Draw an edge connecting parent to child
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(x, y + 25);  // Bottom of the parent's rectangle
            line[1].position = sf::Vector2f(childX, childY - 25);  // Top of the child's rectangle
            line[0].color = sf::Color::Black;
            line[1].color = sf::Color::Black;
            window.draw(line);

            drawNode(window, node->children[i], childX, childY, childOffset, font);  // Recursively draw child node
        }
    }
}

// Draw the BTree using SFML
void BTree::draw(sf::RenderWindow& window, const sf::Font& font) {
    if (root != nullptr) {
        drawNode(window, root, 400, 50, 200, font);  // Starting point for the root node
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
            node->keys.erase(node->keys.begin() + i);  // Remove key from leaf node
        } else {
            // Handle internal node deletion (complex logic needed)
        }
    } else if (!node->isLeaf) {
        deleteValueFromNode(node->children[i], key);  // Recursively delete from child
    }
}
