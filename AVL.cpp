#include "AVL.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <stdexcept>

// Constructor and Destructor
AVL::AVL() : root(nullptr) {}

AVL::~AVL() {
    clear(root);  // Recursively delete all nodes
}

// Insert and Delete Operations
void AVL::insert(int key) {
    root = insert(root, key);  // Insert starting from root
}

void AVL::deleteValue(int key) {
    root = deleteNode(root, key);  // Delete starting from root
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
    return calculateOrder(root, key, order);  // Order calculation
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

// AVL Tree Drawing
void AVL::draw(sf::RenderWindow& window, const sf::Font& font) {
    if (!root) return;

    float xOffset = 400.0f;  // Initial horizontal offset
    drawNode(window, root, font, window.getSize().x / 2.0f, 50.0f, xOffset);
}

void AVL::drawNode(sf::RenderWindow& window, AVLNode* node, const sf::Font& font,
                   float x, float y, float xOffset) const {
    if (!node) return;

    const float yOffset = 75.0f;  // Vertical distance between nodes

    // Draw left subtree
    if (node->left) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y + 20), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x - xOffset, y + yOffset), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawNode(window, node->left, font, x - xOffset, y + yOffset, xOffset / 2.0f);
    }

    // Draw right subtree
    if (node->right) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y + 20), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x + xOffset, y + yOffset), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawNode(window, node->right, font, x + xOffset, y + yOffset, xOffset / 2.0f);
    }

    // Draw node (circle and key)
    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color::White);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(2);
    circle.setPosition(x - 20, y);
    window.draw(circle);

    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(node->key));
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x - 10, y + 5);
    window.draw(text);
}

// Internal Recursive Helper Functions

void AVL::clear(AVLNode* node) {
    if (node != nullptr) {
        clear(node->left);   // Recursively delete left subtree
        clear(node->right);  // Recursively delete right subtree
        delete node;         // Delete current node
    }
}

AVLNode* AVL::insert(AVLNode* node, int key) {
    if (node == nullptr) {
        return new AVLNode(key);  // Create new node if the tree is empty
    }

    if (key < node->key) {
        node->left = insert(node->left, key);  // Insert in left subtree
    } else if (key > node->key) {
        node->right = insert(node->right, key);  // Insert in right subtree
    } else {
        return node;  // Duplicate key is not inserted
    }

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));  // Update height
    return balance(node);  // Balance the tree and return the new root
}

AVLNode* AVL::deleteNode(AVLNode* node, int key) {
    if (node == nullptr) {
        return node;  // Key not found
    }

    // Recur down the tree
    if (key < node->key) {
        node->left = deleteNode(node->left, key);
    } else if (key > node->key) {
        node->right = deleteNode(node->right, key);
    } else {
        // Node with one or no child
        if ((node->left == nullptr) || (node->right == nullptr)) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;  // Copy the contents of the non-empty child
            }
            delete temp;
        } else {
            // Node with two children: Get the inorder successor
            AVLNode* temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);  // Delete the inorder successor
        }
    }

    if (node == nullptr) return node;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));  // Update height
    return balance(node);  // Balance the tree
}

int AVL::calculateDepth(AVLNode* node, int key, int depth) const {
    if (node == nullptr) {
        return -1;  // Key not found
    }
    if (node->key == key) {
        return depth;  // Found the key
    }

    int leftDepth = calculateDepth(node->left, key, depth + 1);
    if (leftDepth != -1) return leftDepth;

    return calculateDepth(node->right, key, depth + 1);
}

int AVL::calculateOrder(AVLNode* node, int key, int& order) const {
    if (node == nullptr) {
        return -1;  // Key not found
    }

    int leftOrder = calculateOrder(node->left, key, order);
    if (leftOrder != -1) return leftOrder;

    if (node->key == key) {
        return order;  // Return the in-order position
    }
    order++;  // Increment order for the next node
    return calculateOrder(node->right, key, order);
}

int AVL::getHeight(AVLNode* node) const {
    return (node == nullptr) ? 0 : node->height;
}

int AVL::getBalanceFactor(AVLNode* node) const {
    return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
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

AVLNode* AVL::minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// Balance the AVL tree
AVLNode* AVL::balance(AVLNode* node) {
    int balanceFactor = getBalanceFactor(node);

    // Left heavy (Right rotation)
    if (balanceFactor > 1) {
        // Left-Right case (double rotation)
        if (getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);  // Left-Right rotation
        }
        return rotateRight(node);  // Right rotation
    }

    // Right heavy (Left rotation)
    if (balanceFactor < -1) {
        // Right-Left case (double rotation)
        if (getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);  // Right-Left rotation
        }
        return rotateLeft(node);  // Left rotation
    }

    // Node is balanced
    return node;
}
