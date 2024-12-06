// Tasks: Replace the placeholder menu options with: ADT selection, operations: Insert, Delete， Search. Import values from a file. Add fuctionality to capture and display values in real-time. Allows users to browse and select a file. Parse the file and  populate the selected adt.
// Describe each step. Include test cases and how to run the applicaton.
#include "heap.h"
#include "Bst.h"
#include "Stack.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include "AVL.h"
#include "BTree.h"
#include "RedBlack.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

// Enum for ADT types
enum class ADTType { HEAP, BST, AVL, BTREE, STACK, QUEUE, PRIORITY_QUEUE, RED_BLACK_TREE };

// Application State Enum
enum class AppState { MAIN_MENU, ADT_SELECTION, ADT_OPERATIONS };

// Simple Menu class
class Menu {
private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menuItems;

public:
    Menu(float width, float height, const std::vector<std::string>& options) {
        if (!font.loadFromFile("edosz.ttf")) {
            std::cerr << "Failed to load font!\n";
        }

        for (size_t i = 0; i < options.size(); ++i) {
            sf::Text text;
            text.setFont(font);
            text.setString(options[i]);
            text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
            text.setPosition(sf::Vector2f(width / 2 - 50, height / (options.size() + 1) * (i + 1)));
            menuItems.push_back(text);
        }

        selectedItemIndex = 0;
    }

    void draw(sf::RenderWindow& window) {
        for (const auto& item : menuItems) {
            window.draw(item);
        }
    }

    void moveUp() {
        if (selectedItemIndex - 1 >= 0) {
            menuItems[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex--;
            menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
        }
    }

    void moveDown() {
        if (selectedItemIndex + 1 < menuItems.size()) {
            menuItems[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex++;
            menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
        }
    }

    int getSelectedItemIndex() const {
        return selectedItemIndex;
    }
};

std::string browseFile() {
    std::cout << "Simulating file selection... (default: sample.txt)\n";
    return "sample.txt";
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Menu with ADTs");
    AppState appState = AppState::MAIN_MENU;

    Menu mainMenu(window.getSize().x, window.getSize().y, {"Select ADT", "Insert", "Delete", "Search", "Import from File"});
    Menu adtMenu(window.getSize().x, window.getSize().y, {"Heap", "BST", "AVL", "BTree", "Stack", "Queue", "Priority Queue", "Red-Black Tree"});
    Menu operationMenu(window.getSize().x, window.getSize().y, {"Insert", "Delete", "Search"});

    ADTType currentADT = ADTType::HEAP; // Default ADT

    // ADT Instances
    Heap heap;
    BST bst;
    AVL avl;
    BTree btree(3);
    RedBlackTree rbt;
    Stack stack;
    Queue queue;
    PriorityQueue priorityQueue;

    bool inputMode = false;
    std::string inputBuffer;
    int selectedOption = -1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                switch (appState) {
                case AppState::MAIN_MENU:
                    if (event.key.code == sf::Keyboard::Up) {
                        mainMenu.moveUp();
                    } else if (event.key.code == sf::Keyboard::Down) {
                        mainMenu.moveDown();
                    } else if (event.key.code == sf::Keyboard::Enter) {
                        selectedOption = mainMenu.getSelectedItemIndex();
                        if (selectedOption == 0) { // Go to ADT selection
                            appState = AppState::ADT_SELECTION;
                        } else if (selectedOption == 4) { // Import from file
                            std::string fileName = browseFile();
                            std::cout << "Importing from file: " << fileName << "\n";
                            if (currentADT == ADTType::AVL) avl.parseFromFile(fileName);
                            else if (currentADT == ADTType::HEAP) heap.parseFromFile(fileName);
                            else if (currentADT == ADTType::BST) bst.parseFromFile(fileName);
                            else if (currentADT == ADTType::BTREE) btree.parseFromFile(fileName);
                            else if (currentADT == ADTType::RED_BLACK_TREE) rbt.parseFromFile(fileName);
                            else if (currentADT == ADTType::PRIORITY_QUEUE) priorityQueue.parseFromFile(fileName);
                            else std::cerr << "File import not supported for Stack/Queue.\n";
                        }
                    }
                    break;

                case AppState::ADT_SELECTION:
                    if (event.key.code == sf::Keyboard::Up) {
                        adtMenu.moveUp();
                    } else if (event.key.code == sf::Keyboard::Down) {
                        adtMenu.moveDown();
                    } else if (event.key.code == sf::Keyboard::Enter) {
                        currentADT = static_cast<ADTType>(adtMenu.getSelectedItemIndex());
                        appState = AppState::ADT_OPERATIONS;
                        std::cout << "ADT selected.\n";
                    }
                    break;

                case AppState::ADT_OPERATIONS:
                    if (event.key.code == sf::Keyboard::Up) {
                        operationMenu.moveUp();
                    } else if (event.key.code == sf::Keyboard::Down) {
                        operationMenu.moveDown();
                    } else if (event.key.code == sf::Keyboard::Enter) {
                        int operation = operationMenu.getSelectedItemIndex();
                        inputMode = true;
                        std::cout << (operation == 0 ? "Insert" : operation == 1 ? "Delete" : "Search") << " value: ";
                    }
                    break;
                }
            }

            if (inputMode && event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\r') { // Enter
                    try {
                        int value = std::stoi(inputBuffer);
                        if (operationMenu.getSelectedItemIndex() == 0) { // Insert
                            if (currentADT == ADTType::HEAP) heap.insert(value);
                            else if (currentADT == ADTType::BST) bst.insert(value);
                            // Repeat for other ADTs
                        } else if (operationMenu.getSelectedItemIndex() == 1) { // Delete
                            if (currentADT == ADTType::HEAP) heap.deleteValue(value);
                            else if (currentADT == ADTType::BST) bst.deleteValue(value);
                            // Repeat for other ADTs
                        } else if (operationMenu.getSelectedItemIndex() == 2) { // Search
                            bool found = false;
                            if (currentADT == ADTType::HEAP) found = heap.search(value);
                            else if (currentADT == ADTType::BST) found = bst.search(value);
                            // Repeat for other ADTs
                            std::cout << (found ? "Found" : "Not found") << "\n";
                        }
                    } catch (const std::exception& e) {
                        std::cerr << "Invalid input: " << e.what() << "\n";
                    }

                    inputMode = false;
                    inputBuffer.clear();
                } else if (event.text.unicode == 8 && !inputBuffer.empty()) { // Backspace
                    inputBuffer.pop_back();
                } else if (event.text.unicode < 128) { // Valid ASCII
                    inputBuffer += static_cast<char>(event.text.unicode);
                }
            }
        }

        window.clear();

        switch (appState) {
        case AppState::MAIN_MENU:
            mainMenu.draw(window);
            break;

        case AppState::ADT_SELECTION:
            adtMenu.draw(window);
            break;

        case AppState::ADT_OPERATIONS:
            operationMenu.draw(window);
            break;
        }

        window.display();
    }

    return 0;
}

