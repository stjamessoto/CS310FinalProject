//AVL.cpp
#include "AVL.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>  

// Constructor and Destructor
AVL::AVL() : root(nullptr) {}

AVL::~AVL() {
    clear(root);
}

// Insert and Delete Operations
void AVL::insert(int key) {
    root = insert(root, key);
}

void AVL::deleteValue(int key) {
    root = deleteNode(root, key);
}

// Parsing from File
void AVL::parseFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << fileName << "\n";
        return;
    }
    int value;
    while (file >> value) {
        insert(value);
    }
    file.close();
}

// Print Function
void AVL::print() const {
    if (root == nullptr) {
        std::cout << "The AVL tree is empty.\n";
    } else {
        std::cout << "AVL Tree (In-Order Traversal): ";
        printInOrder(root);  // Helper function for in-order print
        std::cout << "\n";
    }
}

// Helper function for in-order traversal
void AVL::printInOrder(AVLNode* node) const {
    if (node == nullptr) return;

    printInOrder(node->left);  // Left subtree
    std::cout << node->key << " ";  // Print key
    printInOrder(node->right);  // Right subtree
}

// Get Depth and Order of Node
int AVL::getDepth(int key) const {
    return calculateDepth(root, key, 0);  // Depth calculation
}

int AVL::getOrder(int key) const {
    int order = 1; // Order starts at 1
    calculateOrder(root, key, order);  // Order calculation
    return order;
}

// Return a vector of all keys in in-order traversal
std::vector<int> AVL::getData() const {
    std::vector<int> keys;
    inOrderTraversal(root, keys);  // Populate the vector with keys from the tree
    return keys;
}

// Modified inOrderTraversal to accept a vector to store the keys
void AVL::inOrderTraversal(AVLNode* node, std::vector<int>& keys) const {
    if (node != nullptr) {
        inOrderTraversal(node->left, keys);  // Left
        keys.push_back(node->key);  // Add key to vector
        inOrderTraversal(node->right, keys);  // Right
    }
}

// AVL Tree Node Insertion and Deletion
AVLNode* AVL::insert(AVLNode* node, int key) {
    if (!node) return new AVLNode(key);  // Create new node if empty

    if (key < node->key)
        node->left = insert(node->left, key);  // Insert into left subtree
    else if (key > node->key)
        node->right = insert(node->right, key);  // Insert into right subtree
    else
        return node;  // Duplicates not allowed

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));  // Update height

    int balance = getBalanceFactor(node);

    // Left Left case
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    // Right Right case
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    // Left Right case
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left case
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;  // Return the (possibly rotated) node
}

AVLNode* AVL::deleteNode(AVLNode* node, int key) {
    if (!node) return node;

    // Recur down the tree
    if (key < node->key)
        node->left = deleteNode(node->left, key);
    else if (key > node->key)
        node->right = deleteNode(node->right, key);
    else {
        // Node with one or no children
        if (!node->left || !node->right) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            // Node with two children: get the inorder successor
            AVLNode* temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
    }

    // If the tree had only one node, return
    if (!node) return node;

    // Update height of the current node
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    int balance = getBalanceFactor(node);

    // Left Left case
    if (balance > 1 && getBalanceFactor(node->left) >= 0)
        return rotateRight(node);

    // Left Right case
    if (balance > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Right case
    if (balance < -1 && getBalanceFactor(node->right) <= 0)
        return rotateLeft(node);

    // Right Left case
    if (balance < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

AVLNode* AVL::minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left)
        current = current->left;
    return current;
}

int AVL::getHeight(AVLNode* node) const {
    return node ? node->height : 0;
}

int AVL::getBalanceFactor(AVLNode* node) const {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

AVLNode* AVL::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLNode* AVL::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

void AVL::clear(AVLNode* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

int AVL::calculateDepth(AVLNode* node, int key, int depth) const {
    if (!node) return -1;  // Node not found
    if (key == node->key) return depth;
    if (key < node->key) return calculateDepth(node->left, key, depth + 1);
    return calculateDepth(node->right, key, depth + 1);
}

int AVL::calculateOrder(AVLNode* node, int key, int& order) const {
    if (!node) return -1;  // Node not found
    if (key < node->key) {
        return calculateOrder(node->left, key, order);
    } else if (key > node->key) {
        order += (node->left ? node->left->height : 0) + 1;  // Add left subtree size
        return calculateOrder(node->right, key, order);
    }
    if (node->left) order += node->left->height;
    return order;  // Key found
}

// Search Function
bool AVL::search(int key) const {
    return searchHelper(root, key);  // Helper function for searching
}

// The missing searchHelper function
bool AVL::searchHelper(AVLNode* node, int key) const {
    if (node == nullptr) {
        return false;  // Key not found
    }
    if (key == node->key) {
        return true;  // Key found
    }
    if (key < node->key) {
        return searchHelper(node->left, key);  // Search in the left subtree
    } else {
        return searchHelper(node->right, key);  // Search in the right subtree
    }
}

void AVL::draw(sf::RenderWindow& window) {
    // For drawing AVL Tree, you need to implement visualization with SFML (optional)
}

void AVL::display() const {
    print();  // Display AVL tree using in-order traversal
}
