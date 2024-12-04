//BTree.cpp
#include "BTree.h"

// BTreeNode constructor
BTreeNode::BTreeNode(int t, bool isLeaf) : t(t), isLeaf(isLeaf) {}

// Traverse the tree
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!isLeaf) {
            children[i]->traverse();
        }
        std::cout << keys[i] << " ";
    }
    if (!isLeaf) {
        children[i]->traverse();
    }
}

// Search for a key
bool BTreeNode::search(int key) {
    int i = 0;
    while (i < keys.size() && key > keys[i]) {
        i++;
    }
    if (i < keys.size() && keys[i] == key) {
        return true;
    }
    if (isLeaf) {
        return false;
    }
    return children[i]->search(key);
}

// Insert into a non-full node
void BTreeNode::insertNonFull(int key) {
    int i = keys.size() - 1;

    if (isLeaf) {
        keys.push_back(0); // Allocate space
        while (i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = key;
    } else {
        while (i >= 0 && keys[i] > key) {
            i--;
        }
        i++;
        if (children[i]->keys.size() == 2 * t - 1) {
            splitChild(i, children[i]);
            if (keys[i] < key) {
                i++;
            }
        }
        children[i]->insertNonFull(key);
    }
}

// Split a child node
void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->isLeaf);
    z->keys.resize(t - 1);

    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t];
    }
    if (!y->isLeaf) {
        z->children.resize(t);
        for (int j = 0; j < t; j++) {
            z->children[j] = y->children[j + t];
        }
    }
    y->keys.resize(t - 1);
    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
}

// BTree constructor
BTree::BTree(int t) : root(nullptr), t(t) {}

// Traverse the tree
void BTree::traverse() {
    if (root) {
        root->traverse();
    }
    std::cout << std::endl;
}

// Search for a key
bool BTree::search(int key) {
    return root ? root->search(key) : false;
}

// Insert a key
void BTree::insert(int key) {
    if (!root) {
        root = new BTreeNode(t, true);
        root->keys.push_back(key);
    } else {
        if (root->keys.size() == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->children.push_back(root);
            s->splitChild(0, root);
            int i = (s->keys[0] < key) ? 1 : 0;
            s->children[i]->insertNonFull(key);
            root = s;
        } else {
            root->insertNonFull(key);
        }
    }
}

// Display the tree
void BTree::display() {
    std::cout << "BTree contents: ";
    traverse();
}

// Parse values from a file
void BTree::parseFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return;
    }
    int value;
    while (file >> value) {
        insert(value);
    }
    std::cout << "File imported successfully into BTree.\n";
}
