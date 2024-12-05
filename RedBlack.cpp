// RedBlack.cpp
#include "RedBlack.h"

// Constructor
RedBlackTree::RedBlackTree() {
    TNULL = new RBNode(0);
    TNULL->color = BLACK;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
}

// Destructor
RedBlackTree::~RedBlackTree() {
    while (root != TNULL) {
        deleteValue(root->data);
    }
    delete TNULL;
}

void RedBlackTree::initializeNULLNode(RBNode* node, RBNode* parent) {
    node->data = 0;
    node->parent = parent;
    node->left = TNULL;
    node->right = TNULL;
    node->color = BLACK;
}

// Pre-order helper
void RedBlackTree::preOrderHelper(RBNode* node) {
    if (node != TNULL) {
        std::cout << node->data << " ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }
}

// In-order helper
void RedBlackTree::inOrderHelper(RBNode* node) {
    if (node != TNULL) {
        inOrderHelper(node->left);
        std::cout << node->data << " ";
        inOrderHelper(node->right);
    }
}

// Post-order helper
void RedBlackTree::postOrderHelper(RBNode* node) {
    if (node != TNULL) {
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        std::cout << node->data << " ";
    }
}

// Search tree helper
RBNode* RedBlackTree::searchTreeHelper(RBNode* node, int key) {
    if (node == TNULL || key == node->data) {
        return node;
    }
    if (key < node->data) {
        return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
}

// Insert a new value
void RedBlackTree::insert(int key) {
    RBNode* node = new RBNode(key);
    node->left = TNULL;
    node->right = TNULL;

    RBNode* y = nullptr;
    RBNode* x = root;

    while (x != TNULL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    node->parent = y;
    if (y == nullptr) {
        root = node;
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }

    if (node->parent == nullptr) {
        node->color = BLACK;
        return;
    }
    if (node->parent->parent == nullptr) {
        return;
    }
    balanceInsert(node);
}

// Delete a value
void RedBlackTree::deleteValue(int key) {
    deleteNodeHelper(root, key);
}

// Display the tree
void RedBlackTree::display() {
    if (root != TNULL) {
        inOrderHelper(root);
        std::cout << std::endl;
    } else {
        std::cout << "Tree is empty.\n";
    }
}

// Search for a value
bool RedBlackTree::search(int key) {
    return searchTreeHelper(root, key) != TNULL;
}

// Parse values from a file
void RedBlackTree::parseFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File not found: " << filename << std::endl;
        return;
    }
    int value;
    while (file >> value) {
        insert(value);
    }
    file.close();
}