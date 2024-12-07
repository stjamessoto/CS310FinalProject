#include "Bst.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <vector>

BST::BST() : root(nullptr) {}

BST::~BST() {
    clearTree(root);
}

void BST::insert(int value) {
    root = insertNode(root, value);
}

BST::Node* BST::insertNode(Node* node, int value) {
    if (node == nullptr) {
        return new Node(value);
    }
    if (value < node->value) {
        node->left = insertNode(node->left, value);
    } else if (value > node->value) {
        node->right = insertNode(node->right, value);
    }
    return node;
}

void BST::deleteValue(int value) {
    root = deleteNode(root, value);
}

BST::Node* BST::deleteNode(Node* node, int value) {
    if (node == nullptr) {
        return node;
    }

    if (value < node->value) {
        node->left = deleteNode(node->left, value);
    } else if (value > node->value) {
        node->right = deleteNode(node->right, value);
    } else {
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        Node* temp = findMin(node->right);
        node->value = temp->value;
        node->right = deleteNode(node->right, temp->value);
    }
    return node;
}

BST::Node* BST::findMin(Node* node) {
    Node* current = node;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

bool BST::search(int value) {
    return searchNode(root, value);
}

bool BST::searchNode(Node* node, int value) {
    if (node == nullptr) {
        return false;
    }
    if (value == node->value) {
        return true;
    }
    return value < node->value ? searchNode(node->left, value) : searchNode(node->right, value);
}

// New contains method
bool BST::contains(int value) {
    return search(value);  // Delegates to the search function
}

void BST::inorderTraversal(Node* node, std::ostream& os) const {
    if (node == nullptr) return;
    inorderTraversal(node->left, os);
    os << node->value << " ";  // Write the node value to the output stream
    inorderTraversal(node->right, os);
}

void BST::displayTree() const {
    inorderTraversal(root, std::cout);  // Print to console
    std::cout << std::endl;
}

void BST::clearTree(Node* node) {
    if (node == nullptr) return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

void BST::parseFromFile(const std::string& fileName) {
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

// Helper function to draw nodes
void BST::drawNode(sf::RenderWindow& window, Node* node, float x, float y, float offset) const {
    if (node == nullptr) return;

    // Draw the node value as a circle
    sf::CircleShape nodeShape(20);
    nodeShape.setFillColor(sf::Color::Green);
    nodeShape.setPosition(x - 20, y - 20);
    window.draw(nodeShape);

    // Draw the text value inside the circle
    sf::Font font;
    if (!font.loadFromFile("edosz.ttf")) {
        std::cerr << "Error loading font.\n";
    }
    sf::Text text(std::to_string(node->value), font, 18);
    text.setFillColor(sf::Color::White);
    text.setPosition(x - 10, y - 10);
    window.draw(text);

    // Draw edges (lines) to left and right children
    if (node->left) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y)),
            sf::Vertex(sf::Vector2f(x - offset, y + 50))
        };
        window.draw(line, 2, sf::Lines);
        drawNode(window, node->left, x - offset, y + 50, offset / 2);
    }
    if (node->right) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y)),
            sf::Vertex(sf::Vector2f(x + offset, y + 50))
        };
        window.draw(line, 2, sf::Lines);
        drawNode(window, node->right, x + offset, y + 50, offset / 2);
    }
}

// Public function to draw the entire tree
void BST::draw(sf::RenderWindow& window, const sf::Font& font) {
    drawNode(window, root, window.getSize().x / 2, 50, 200);
}

// New print function
void BST::print() const {
    std::cout << "Binary Search Tree (rotated 90 degrees):\n";
    printTree(root, 0);
}

// Helper function for print
void BST::printTree(Node* node, int space, int indent) const {
    if (node == nullptr) return;

    // Increase distance between levels
    space += indent;

    // Print right child first
    printTree(node->right, space, indent);

    // Print current node after spacing
    std::cout << std::endl;
    for (int i = indent; i < space; i++) std::cout << " ";
    std::cout << node->value << "\n";

    // Print left child
    printTree(node->left, space, indent);
}

// Method to get tree data as a vector of integers
std::vector<int> BST::getData() const {
    std::vector<int> data;
    inorderTraversal(root, data);  // Perform inorder traversal and fill the vector
    return data;
}

// Helper method for inorder traversal that fills a vector
void BST::inorderTraversal(Node* node, std::vector<int>& data) const {
    if (node == nullptr) return;
    inorderTraversal(node->left, data);
    data.push_back(node->value);  // Add node value to the vector
    inorderTraversal(node->right, data);
}

BST::Node* BST::getRoot() const {
    return root;
}
