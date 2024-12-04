//AVL.cpp
#include "AVL.h"

AVL::AVL() : root(nullptr) {}

AVL::~AVL() {
    clear(root);
}

void AVL::insert(int key) {
    root = insert(root, key);
}

AVLNode* AVL::insert(AVLNode* node, int key) {
    if (!node) return new AVLNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // Duplicate keys not allowed

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    int balance = getBalanceFactor(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVL::deleteValue(int key) {
    root = deleteNode(root, key);
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

    // Left Left Case
    if (balance > 1 && getBalanceFactor(node->left) >= 0)
        return rotateRight(node);

    // Left Right Case
    if (balance > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Right Case
    if (balance < -1 && getBalanceFactor(node->right) <= 0)
        return rotateLeft(node);

    // Right Left Case
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

bool AVL::search(int key) const {
    AVLNode* current = root;
    while (current) {
        if (key == current->key)
            return true;
        else if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }
    return false;
}

void AVL::parseFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Failed to open file: " << fileName << '\n';
        return;
    }

    int value;
    while (file >> value) {
        insert(value);
    }

    file.close();
}

void AVL::display() const {
    std::cout << "In-order Traversal: ";
    inOrderTraversal(root);
    std::cout << '\n';
}

void AVL::inOrderTraversal(AVLNode* node) const {
    if (node) {
        inOrderTraversal(node->left);
        std::cout << node->key << " ";
        inOrderTraversal(node->right);
    }
}

int AVL::getHeight(AVLNode* node) const {
    return node ? node->height : 0;
}

int AVL::getBalanceFactor(AVLNode* node) const {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

AVLNode* AVL::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T = x->right;

    x->right = y;
    y->left = T;

    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));

    return x;
}

AVLNode* AVL::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T = y->left;

    y->left = x;
    x->right = T;

    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

    return y;
}

void AVL::clear(AVLNode* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}