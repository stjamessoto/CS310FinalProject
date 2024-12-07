#include "RedBlack.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>

RedBlackTree::RedBlackTree() {
    TNULL = new RBNode(0);  // Create a sentinel node
    TNULL->color = BLACK;
    root = TNULL;
}

RedBlackTree::~RedBlackTree() {
    clear(root);  // Recursively delete nodes starting from root if necessary
}

void RedBlackTree::clear(RBNode* node) {
    if (node != TNULL) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
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

bool RedBlackTree::contains(int key) {
    return search(key);  // Calls the existing search method
}

bool RedBlackTree::search(int key) {
    RBNode* node = searchTreeHelper(root, key);
    return (node != TNULL);  // Returns true if found, false otherwise
}

void RedBlackTree::insert(int key) {
    RBNode* node = new RBNode(key);
    node->parent = nullptr;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = RED;  // New node is always red initially

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
        root = node;  // Tree was empty
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

    balanceInsert(node);  // Balance the tree after insertion
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

        if (node->data < key)  // Fix comparison here
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
        balanceDelete(x);  // Balance the tree after deletion
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

void RedBlackTree::balanceInsert(RBNode* k) {
    RBNode* u;
    while (k->parent->color == RED) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(k->parent->parent);
            }
        } else {
            u = k->parent->parent->right;
            if (u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root)
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

void RedBlackTree::display() {
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

void RedBlackTree::draw(sf::RenderWindow& window, const sf::Font& font) {
    drawNode(window, root, 400, 50, font);  // Draw the tree starting from root
}

void RedBlackTree::drawNode(sf::RenderWindow& window, RBNode* node, float x, float y, const sf::Font& font) {
    if (node == TNULL) return;

    // Draw the current node's value
    sf::CircleShape circle(20);
    circle.setFillColor(node->color == RED ? sf::Color::Red : sf::Color::Black);
    circle.setPosition(x - 20, y - 20);
    window.draw(circle);

    // Display the value as text
    sf::Text text(std::to_string(node->data), font, 15);
    text.setFillColor(sf::Color::White);
    text.setPosition(x - 10, y - 10);
    window.draw(text);

    // Draw left and right child nodes
    if (node->left != TNULL) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y)),
            sf::Vertex(sf::Vector2f(x - 50, y + 50))
        };
        window.draw(line, 2, sf::Lines);
        drawNode(window, node->left, x - 50, y + 50, font);
    }

    if (node->right != TNULL) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y)),
            sf::Vertex(sf::Vector2f(x + 50, y + 50))
        };
        window.draw(line, 2, sf::Lines);
        drawNode(window, node->right, x + 50, y + 50, font);
    }
}
