//GUIManager.cpp
// GUIManager.cpp
#include "GUIManager.h"

GUIManager::GUIManager(sf::RenderWindow& win)
    : window(win), currentADT(ADTType::HEAP), inputBuffer(""), inputMode(false), selectedOption(-1), btree(3) {
    adtNames = {
        {ADTType::HEAP, "Heap"},
        {ADTType::BST, "Binary Search Tree"},
        {ADTType::AVL, "AVL Tree"},
        {ADTType::BTREE, "B-Tree"},
        {ADTType::STACK, "Stack"},
        {ADTType::QUEUE, "Queue"},
        {ADTType::PRIORITY_QUEUE, "Priority Queue"},
        {ADTType::RED_BLACK_TREE, "Red-Black Tree"}
    };

    if (!font.loadFromFile("edosz.ttf")) {
        throw std::runtime_error("Error loading font.");
    }
}

sf::Vector2f GUIManager::calculateNodePosition(int value) {
    int depth = avl.getDepth(value); // Ensure this method is implemented in AVL class
    int order = avl.getOrder(value); // Ensure this method is implemented in AVL class
    float x = window.getSize().x / (1 << depth) * order;
    float y = 100.f + depth * 50.f;
    return sf::Vector2f(x, y);
}

void GUIManager::addVisualNode(int value, sf::Vector2f position) {
    TreeNodeVisual nodeVisual;
    nodeVisual.circle.setRadius(20.f);
    nodeVisual.circle.setFillColor(sf::Color::White);
    nodeVisual.circle.setOutlineColor(sf::Color::Black);
    nodeVisual.circle.setOutlineThickness(2);
    nodeVisual.circle.setPosition(position);

    nodeVisual.valueText.setFont(font);
    nodeVisual.valueText.setString(std::to_string(value));
    nodeVisual.valueText.setCharacterSize(20);
    nodeVisual.valueText.setFillColor(sf::Color::Black);
    nodeVisual.valueText.setPosition(position + sf::Vector2f(10.f, 5.f));

    nodeVisual.targetPosition = position;
    visualNodes.push_back(nodeVisual);
}

void GUIManager::highlightNode(int value) {
    try {
        for (auto& node : visualNodes) {
            if (std::stoi(node.valueText.getString()) == value) {
                node.circle.setFillColor(sf::Color::Yellow);
            } else {
                node.circle.setFillColor(sf::Color::White);
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in highlightNode: " << e.what() << "\n";
    }
}

void GUIManager::updateNodePositions() {
    for (auto& node : visualNodes) {
        sf::Vector2f current = node.circle.getPosition();
        sf::Vector2f delta = node.targetPosition - current;
        if (std::abs(delta.x) > 0.5f || std::abs(delta.y) > 0.5f) {
            node.circle.move(delta * 0.1f);
            node.valueText.move(delta * 0.1f);
        }
    }
}

void GUIManager::handleInput(int value) {
    try {
        sf::Vector2f position;
        switch (currentADT) {
            case ADTType::AVL:
                if (selectedOption == 1) {
                    avl.insert(value);
                    position = calculateNodePosition(value);
                    addVisualNode(value, position);
                } else if (selectedOption == 2) {
                    avl.deleteValue(value);
                } else if (selectedOption == 3) {
                    if (avl.search(value)) {
                        highlightNode(value);
                    }
                }
                break;

            case ADTType::RED_BLACK_TREE:
                if (selectedOption == 1) {
                    rbt.insert(value);
                    position = calculateNodePosition(value);
                    addVisualNode(value, position);
                } else if (selectedOption == 2) {
                    rbt.deleteValue(value);
                } else if (selectedOption == 3) {
                    if (rbt.search(value)) {
                        highlightNode(value);
                    }
                }
                break;

            default:
                std::cerr << "ADT operation not supported for this type.\n";
                break;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void GUIManager::render() {
    window.clear();

    updateNodePositions();
    for (const auto& node : visualNodes) {
        window.draw(node.circle);
        window.draw(node.valueText);
    }

    window.display();
}

std::string GUIManager::browseFile() {
    std::cout << "Simulating file selection... (default: sample.txt)\n";
    return "sample.txt";
}

void GUIManager::processEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter && inputMode) {
            try {
                handleInput(std::stoi(inputBuffer)); // Input handling
            } catch (const std::exception& e) {
                std::cerr << "Invalid input: " << e.what() << "\n";
            }
            inputBuffer.clear();
            inputMode = false;
        }
    } else if (event.type == sf::Event::TextEntered && inputMode) {
        if (event.text.unicode < 128) {
            char enteredChar = static_cast<char>(event.text.unicode);
            if (std::isdigit(enteredChar)) { // Ensure numeric input
                inputBuffer += enteredChar;
            }
        }
    }
}