//AVL.cpp
#include "AVL.h"

AVL::AVL() : root(nullptr) {}
AVL::~AVL() { clear(root); }

void AVL::insert(int key) {
    root = insert(root, key);
}

void AVL::deleteValue(int key) {
    root = deleteNode(root, key);
}

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

AVLNode* AVL::insert(AVLNode* node, int key) {
    if (!node) return new AVLNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // Duplicates not allowed

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    int balance = getBalanceFactor(node);

    if (balance > 1 && key < node->left->key) // Left Left
        return rotateRight(node);

    if (balance < -1 && key > node->right->key) // Right Right
        return rotateLeft(node);

    if (balance > 1 && key > node->left->key) { // Left Right
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) { // Right Left
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

AVLNode* AVL::deleteNode(AVLNode* node, int key) {
    if (!node) return node;

    if (key < node->key)
        node->left = deleteNode(node->left, key);
    else if (key > node->key)
        node->right = deleteNode(node->right, key);
    else {
        if (!node->left || !node->right) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else
                *node = *temp;
            delete temp;
        } else {
            AVLNode* temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
    }

    if (!node) return node;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    int balance = getBalanceFactor(node);

    if (balance > 1 && getBalanceFactor(node->left) >= 0) // Left Left
        return rotateRight(node);

    if (balance > 1 && getBalanceFactor(node->left) < 0) { // Left Right
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && getBalanceFactor(node->right) <= 0) // Right Right
        return rotateLeft(node);

    if (balance < -1 && getBalanceFactor(node->right) > 0) { // Right Left
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

    x->right = y;
    y->left = T2;

    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLNode* AVL::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

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

void AVL::inOrderTraversal(AVLNode* node) const {
    if (node) {
        inOrderTraversal(node->left);
        std::cout << node->key << " ";
        inOrderTraversal(node->right);
    }
}

void AVL::display() const {
    inOrderTraversal(root);
    std::cout << std::endl;
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

