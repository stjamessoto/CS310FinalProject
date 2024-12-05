//GUIManager.h
#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <cmath>
#include "heap.h"
#include "Bst.h"
#include "Stack.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include "AVL.h"
#include "BTree.h"
#include "RedBlack.h"

// Enum for ADT Selection
enum class ADTType { HEAP, BST, AVL, BTREE, STACK, QUEUE, PRIORITY_QUEUE, RED_BLACK_TREE };

// Struct for visualizing tree nodes
struct TreeNodeVisual {
    sf::CircleShape circle;
    sf::Text valueText;
    sf::Vector2f targetPosition; // For animation
};

class GUIManager {
private:
    // Core SFML components
    sf::RenderWindow& window;

    // Current state and configuration
    ADTType currentADT;
    std::map<ADTType, std::string> adtNames;

    // ADT instances
    Heap heap;
    BST bst;
    AVL avl;
    BTree btree;
    RedBlackTree rbt;
    Stack stack;
    Queue queue;
    PriorityQueue priorityQueue;

    // Input handling
    std::string inputBuffer;
    bool inputMode;
    int selectedOption;

    // Visualization and Animation
    std::vector<TreeNodeVisual> visualNodes;
    sf::Font font;

    // Helper methods
    void handleInput(int value);
    void highlightNode(int value);
    void addVisualNode(int value, sf::Vector2f position);
    void updateNodePositions();
    sf::Vector2f calculateNodePosition(int value);

public:
    // Constructor
    GUIManager(sf::RenderWindow& win);

    // Core methods
    void processEvent(sf::Event& event);
    void render();
    std::string browseFile();
    void loadInitialData(const std::string& filePath); // Load data from a file
};

#endif // GUIMANAGER_H