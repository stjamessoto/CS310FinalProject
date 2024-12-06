// RedBlack.cpp
#include "RedBlackTree.h"
#include <iostream>
#include <SFML/Graphics.hpp>

RedBlackTree::RedBlackTree() {
    TNULL = new RBNode(0);  // Create a sentinel node
    TNULL->color = BLACK;
    root = TNULL;
}

RedBlackTree::~RedBlackTree() {
    // Recursively delete nodes starting from root
    // Add your clear function here if necessary
}

void RedBlackTree::initializeNULLNode(RBNode* node, RBNode* parent) {
    node->parent = parent;
    node->left = TNULL;
    node->right = TNULL;
    node->color = BLACK;
}

void RedBlackTree::preOrderHelper(RBNode* node) {
    if (node != TNULL) {
        std::cout << node->data << " ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }
}

void RedBlackTree::inOrderHelper(RBNode* node) {
    if (node != TNULL) {
        inOrderHelper(node->left);
        std::cout << node->data << " ";
        inOrderHelper(node->right);
    }
}

void RedBlackTree::postOrderHelper(RBNode* node) {
    if (node != TNULL) {
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        std::cout << node->data << " ";
    }
}

RBNode* RedBlackTree::searchTreeHelper(RBNode* node, int key) {
    if (node == TNULL || key == node->data)
        return node;

    if (key < node->data)
        return searchTreeHelper(node->left, key);
    else
        return searchTreeHelper(node->right, key);
}

void RedBlackTree::balanceInsert(RBNode* node) {
    RBNode* uncle;

    while (node->parent->color == RED) {
        if (node->parent == node->parent->parent->right) {
            uncle = node->parent->parent->left;
            if (uncle->color == RED) {
                // Case 1: Uncle is red
                uncle->color = BLACK;
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    // Case 2: Node is left child
                    node = node->parent;
                    rightRotate(node);
                }
                // Case 3: Node is right child
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                leftRotate(node->parent->parent);
            }
        } else {
            uncle = node->parent->parent->right;
            if (uncle->color == RED) {
                // Case 1: Uncle is red
                uncle->color = BLACK;
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    // Case 2: Node is right child
                    node = node->parent;
                    leftRotate(node);
                }
                // Case 3: Node is left child
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightRotate(node->parent->parent);
            }
        }
        if (node == root)
            break;
    }
    root->color = BLACK;
}

void RedBlackTree::leftRotate(RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left != TNULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(RBNode* x) {
    RBNode* y = x->left;
    x->left = y->right;
    if (y->right != TNULL)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void RedBlackTree::insert(int key) {
    RBNode* node = new RBNode(key);
    node->parent = nullptr;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = RED;

    RBNode* y = nullptr;
    RBNode* x = root;

    while (x != TNULL) {
        y = x;
        if (node->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    node->parent = y;
    if (y == nullptr)
        root = node;
    else if (node->data < y->data)
        y->left = node;
    else
        y->right = node;

    if (node->parent == nullptr) {
        node->color = BLACK;
        return;
    }

    if (node->parent->parent == nullptr)
        return;

    balanceInsert(node);
}

bool RedBlackTree::search(int key) {
    RBNode* node = searchTreeHelper(root, key);
    return (node != TNULL);
}

void RedBlackTree::deleteValue(int key) {
    deleteNodeHelper(root, key);
}

void RedBlackTree::deleteNodeHelper(RBNode* node, int key) {
    RBNode* z = TNULL;
    RBNode* x, *y;
    while (node != TNULL) {
        if (node->data == key) {
            z = node;
        }

        if (node->data <= key)
            node = node->right;
        else
            node = node->left;
    }

    if (z == TNULL)
        return;

    y = z;
    Color yOriginalColor = y->color;
    if (z->left == TNULL) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == TNULL) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (yOriginalColor == BLACK)
        balanceDelete(x);
}

void RedBlackTree::transplant(RBNode* u, RBNode* v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

RBNode* RedBlackTree::minimum(RBNode* node) {
    while (node->left != TNULL)
        node = node->left;
    return node;
}

void RedBlackTree::balanceDelete(RBNode* x) {
    RBNode* w;
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }

            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void RedBlackTree::display() {
    // Implement this function if needed for printing or debugging.
    // For example, you could use inOrderHelper for an in-order traversal print
    inOrderHelper(root);
    std::cout << std::endl;
}

void RedBlackTree::print() {
    std::cout << "In-order Traversal: ";
    inOrderHelper(root);
    std::cout << std::endl;
}

void RedBlackTree::parseFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        int value;
        while (file >> value) {
            insert(value);
        }
    }
    file.close();
}

void RedBlackTree::draw(sf::RenderWindow& window) {
    // Implement drawing the tree structure with SFML here
    // Consider writing a recursive helper function to draw nodes and edges
}

