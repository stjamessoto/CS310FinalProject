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

// Simple Menu class definition
class Menu {
private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menuItems;

public:
    Menu(float width, float height) {
        if (!font.loadFromFile("edosz.ttf")) {
            std::cerr << "Failed to load font!\n";
        }

        std::vector<std::string> options = {"Select ADT", "Insert", "Delete", "Search", "Import from File"};
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

enum class ADTType { HEAP, BST, AVL, BTREE, STACK, QUEUE, PRIORITY_QUEUE, RED_BLACK_TREE };

std::string browseFile() {
    std::cout << "Simulating file selection... (default: sample.txt)\n";
    return "sample.txt";
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Menu with ADTs");
    Menu menu(window.getSize().x, window.getSize().y);
    Heap heap;                 // Heap instance
    BST bst;                   // BST instance
    AVL avl;                   // AVL tree instance
    BTree btree(3);            // BTree instance (minimum degree 3)
    RedBlackTree rbt;          // Red-Black Tree instance
    Stack stack;               // Stack instance
    Queue queue;               // Queue instance
    PriorityQueue priorityQueue; // PriorityQueue instance

    ADTType currentADT = ADTType::HEAP; // Default to Heap
    std::string inputBuffer;
    bool inputMode = false;
    int selectedOption = -1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    menu.moveUp();
                } else if (event.key.code == sf::Keyboard::Down) {
                    menu.moveDown();
                } else if (event.key.code == sf::Keyboard::Enter) {
                    selectedOption = menu.getSelectedItemIndex();
                    switch (selectedOption) {
                        case 0: { // ADT Selection
                            std::cout << "Select ADT (1 for Heap, 2 for BST, 3 for AVL, 4 for BTree, 5 for Stack, 6 for Queue, 7 for Priority Queue, 8 for Red-Black Tree): ";
                            int choice;
                            std::cin >> choice;
                            switch (choice) {
                                case 1: currentADT = ADTType::HEAP; break;
                                case 2: currentADT = ADTType::BST; break;
                                case 3: currentADT = ADTType::AVL; break;
                                case 4: currentADT = ADTType::BTREE; break;
                                case 5: currentADT = ADTType::STACK; break;
                                case 6: currentADT = ADTType::QUEUE; break;
                                case 7: currentADT = ADTType::PRIORITY_QUEUE; break;
                                case 8: currentADT = ADTType::RED_BLACK_TREE; break;
                                default: std::cerr << "Invalid choice.\n"; break;
                            }
                            std::cout << (choice == 1 ? "Heap selected.\n" :
                                         choice == 2 ? "BST selected.\n" :
                                         choice == 3 ? "AVL selected.\n" :
                                         choice == 4 ? "BTree selected.\n" :
                                         choice == 5 ? "Stack selected.\n" :
                                         choice == 6 ? "Queue selected.\n" :
                                         choice == 7 ? "Priority Queue selected.\n" :
                                         "Red-Black Tree selected.\n");
                            break;
                        }
                        case 1: // Insert
                            inputMode = true;
                            inputBuffer = "";
                            std::cout << "Enter value to insert:\n";
                            break;
                        case 2: // Delete
                            inputMode = true;
                            inputBuffer = "";
                            std::cout << "Enter value to delete:\n";
                            break;
                        case 3: // Search
                            inputMode = true;
                            inputBuffer = "";
                            std::cout << "Enter value to search:\n";
                            break;
                        case 4: { // Import values from file
                            std::string fileName = browseFile();
                            std::cout << "Importing from file: " << fileName << "\n";
                            if (currentADT == ADTType::AVL) {
                                avl.parseFromFile(fileName);
                                avl.display();
                            } else if (currentADT == ADTType::HEAP) {
                                heap.parseFromFile(fileName);
                                heap.displayHeap();
                            } else if (currentADT == ADTType::BST) {
                                bst.parseFromFile(fileName);
                                bst.displayTree();
                            } else if (currentADT == ADTType::BTREE) {
                                btree.parseFromFile(fileName);
                                btree.display();
                            } else if (currentADT == ADTType::RED_BLACK_TREE) {
                                rbt.parseFromFile(fileName);
                                rbt.display();
                            } else if (currentADT == ADTType::PRIORITY_QUEUE) {
                                priorityQueue.parseFromFile(fileName);
                                priorityQueue.display();
                            } else {
                                std::cerr << "File import not supported for Stack/Queue.\n";
                            }
                            break;
                        }
                        default:
                            break;
                    }
                }
            }

            if (inputMode && event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\r') { // Enter key
                    try {
                        int value = std::stoi(inputBuffer);
                        if (currentADT == ADTType::AVL) {
                            if (selectedOption == 1) avl.insert(value);
                            else if (selectedOption == 2) avl.deleteValue(value);
                            else if (selectedOption == 3)
                                std::cout << (avl.search(value) ? "Value found.\n" : "Value not found.\n");
                            avl.display();
                        } else if (currentADT == ADTType::HEAP) {
                            if (selectedOption == 1) heap.insert(value);
                            else if (selectedOption == 2) heap.deleteValue(value);
                            else if (selectedOption == 3)
                                std::cout << (heap.search(value) ? "Value found.\n" : "Value not found.\n");
                            heap.displayHeap();
                        } else if (currentADT == ADTType::BST) {
                            if (selectedOption == 1) bst.insert(value);
                            else if (selectedOption == 2) bst.deleteValue(value);
                            else if (selectedOption == 3)
                                std::cout << (bst.search(value) ? "Value found.\n" : "Value not found.\n");
                            bst.displayTree();
                        } else if (currentADT == ADTType::BTREE) {
                            if (selectedOption == 1) btree.insert(value);
                            else if (selectedOption == 3)
                                std::cout << (btree.search(value) ? "Value found.\n" : "Value not found.\n");
                            btree.display();
                        } else if (currentADT == ADTType::RED_BLACK_TREE) {
                            if (selectedOption == 1) rbt.insert(value);
                            else if (selectedOption == 2) rbt.deleteValue(value);
                            else if (selectedOption == 3)
                                std::cout << (rbt.search(value) ? "Value found.\n" : "Value not found.\n");
                            rbt.display();
                        }
                    } catch (const std::exception& e) {
                        std::cerr << "Invalid input: " << inputBuffer << "\n";
                    }
                    inputMode = false;
                } else if (event.text.unicode == 8 && !inputBuffer.empty()) { // Backspace
                    inputBuffer.pop_back();
                    std::cout << "\r" << inputBuffer << " \b";
                } else if (event.text.unicode < 128) { // Valid ASCII input
                    inputBuffer += static_cast<char>(event.text.unicode);
                    std::cout << "\r" << inputBuffer;
                }
            }
        }

        window.clear();
        menu.draw(window);
        window.display();
    }

    return 0;
}
