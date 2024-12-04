#include "Bst.h"

// Constructor
BST::BST() : root(nullptr) {}

// Destructor
BST::~BST() {
    clearTree(root);
}

// Recursive helper to delete the tree
void BST::clearTree(Node* node) {
    if (!node) return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

// Insert a value into the BST
void BST::insert(int value) {
    root = insertNode(root, value);
}

BST::Node* BST::insertNode(Node* node, int value) {
    if (!node) return new Node(value);
    if (value < node->value) {
        node->left = insertNode(node->left, value);
    } else if (value > node->value) {
        node->right = insertNode(node->right, value);
    }
    return node;
}

// Delete a value from the BST
void BST::deleteValue(int value) {
    root = deleteNode(root, value);
}

BST::Node* BST::deleteNode(Node* node, int value) {
    if (!node) return nullptr;

    if (value < node->value) {
        node->left = deleteNode(node->left, value);
    } else if (value > node->value) {
        node->right = deleteNode(node->right, value);
    } else {
        // Node with one or no child
        if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // Node with two children: Get inorder successor
        Node* temp = findMin(node->right);
        node->value = temp->value;
        node->right = deleteNode(node->right, temp->value);
    }
    return node;
}

// Find the node with the minimum value
BST::Node* BST::findMin(Node* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

// Search for a value in the BST
bool BST::search(int value) {
    return searchNode(root, value);
}

bool BST::searchNode(Node* node, int value) {
    if (!node) return false;
    if (value == node->value) return true;
    if (value < node->value) {
        return searchNode(node->left, value);
    }
    return searchNode(node->right, value);
}

// Display the tree's contents (in-order traversal)
void BST::displayTree() const {
    inorderTraversal(root, std::cout);
    std::cout << std::endl;
}

void BST::inorderTraversal(Node* node, std::ostream& os) const {
    if (!node) return;
    inorderTraversal(node->left, os);
    os << node->value << " ";
    inorderTraversal(node->right, os);
}

// Parse and populate the BST from a file
void BST::parseFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Error opening file: " << fileName << "\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int value;
        while (iss >> value) {
            insert(value);
        }
    }
    std::cout << "Tree populated from file.\n";
    displayTree();
}