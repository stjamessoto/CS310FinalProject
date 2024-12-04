//AVL.cpp
#include "AVL.h"

AVL::AVL() : root(nullptr) {}
AVL::~AVL() { clear(root); }

void AVL::insert(int key) { root = insert(root, key); }
void AVL::deleteValue(int key) { root = deleteNode(root, key); }

bool AVL::search(int key) const {
    AVLNode* current = root;
    while (current) {
        if (key == current->key) return true;
        current = (key < current->key) ? current->left : current->right;
    }
    return false;
}

int AVL::getDepth(int key) const {
    return calculateDepth(root, key, 0);
}

int AVL::getOrder(int key) const {
    int order = 1; // Order starts at 1
    calculateOrder(root, key, order);
    return order;
}

int AVL::calculateDepth(AVLNode* node, int key, int depth) const {
    if (!node) return -1; // Node not found
    if (key == node->key) return depth;
    if (key < node->key) return calculateDepth(node->left, key, depth + 1);
    return calculateDepth(node->right, key, depth + 1);
}

int AVL::calculateOrder(AVLNode* node, int key, int& order) const {
    if (!node) return -1; // Node not found
    if (key < node->key) {
        return calculateOrder(node->left, key, order);
    } else if (key > node->key) {
        order += (node->left ? node->left->height : 0) + 1; // Add left subtree size
        return calculateOrder(node->right, key, order);
    }
    if (node->left) order += node->left->height;
    return order; // Key found
}
