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
    delete TNULL; // Delete the sentinel node
}

// Initialize a NULL node
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

// Balance insert (fix the tree after an insert)
void RedBlackTree::balanceInsert(RBNode* node) {
    RBNode* uncle;
    while (node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            uncle = node->parent->parent->right;
            if (uncle->color == RED) {
                // Case 1: Uncle is red
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    // Case 2: node is right child
                    node = node->parent;
                    leftRotate(node);
                }
                // Case 3: node is left child
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightRotate(node->parent->parent);
            }
        } else {
            // Mirror cases for the right child
            uncle = node->parent->parent->left;
            if (uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                leftRotate(node->parent->parent);
            }
        }
        if (node == root) {
            break;
        }
    }
    root->color = BLACK;
}

// Left rotate
void RedBlackTree::leftRotate(RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// Right rotate
void RedBlackTree::rightRotate(RBNode* x) {
    RBNode* y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

// Delete node helper (called for deleteValue)
void RedBlackTree::deleteNodeHelper(RBNode* node, int key) {
    RBNode* z = TNULL;
    RBNode* x, *y;
    while (node != TNULL) {
        if (node->data == key) {
            z = node;
        }

        if (node->data <= key) {
            node = node->right;
        } else {
            node = node->left;
        }
    }

    if (z == TNULL) {
        std::cout << "Couldn't find key in the tree!" << std::endl;
        return;
    }

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
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (yOriginalColor == BLACK) {
        balanceDelete(x);
    }
}

// Balance delete (fix the tree after a delete)
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

// Transplant helper function (replaces one subtree with another)
void RedBlackTree::transplant(RBNode* u, RBNode* v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// Minimum node helper
RBNode* RedBlackTree::minimum(RBNode* node) {
    while (node->left != TNULL) {
        node = node->left;
    }
    return node;
}

// Insert a value
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

    if (file.bad()) {
        throw std::runtime_error("Error reading file:" + filename);
    }
    file.close();
}
