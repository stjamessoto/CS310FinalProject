#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <atomic>
#include <filesystem>
#include "heap.h"
#include "Bst.h"
#include "Stack.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include "AVL.h"
#include "BTree.h"
#include "RedBlack.h"

// Enums for ADT and Application State
enum class ADTType { HEAP, BST, AVL, BTREE, STACK, QUEUE, PRIORITY_QUEUE, RED_BLACK_TREE };
enum class AppState { MAIN_MENU, ADT_SELECTION, ADT_OPERATIONS, VIEW_ADT };

// Menu class for navigation
class Menu {
private:
    int selectedItemIndex;
    std::vector<sf::Text> menuItems;

public:
    Menu(float width, float height, const std::vector<std::string>& options, const sf::Font& font) {
        for (size_t i = 0; i < options.size(); ++i) {
            sf::Text text;
            text.setFont(font);
            text.setString(options[i]);
            text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
            text.setPosition(sf::Vector2f(width / 2 - 100, height / (options.size() + 1) * (i + 1)));
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

// Load data from file and insert into all ADTs
void loadDataFromFile(const std::string& filename, std::vector<int>& data, std::atomic<bool>& done,
                      ADTType currentADT, Heap& heap, BST& bst, AVL& avl, Stack& stack, Queue& queue,
                      BTree& btree, PriorityQueue& priorityQueue, RedBlackTree& rbt) {
    std::ifstream file(filename);
    std::string line;

    data.clear();
    while (std::getline(file, line)) {
        try {
            int value = std::stoi(line);
            data.push_back(value);

            // Insert into all ADTs
            heap.insert(value);
            bst.insert(value);
            avl.insert(value);
            stack.push(value);
            queue.enqueue(value);
            btree.insert(value);
            priorityQueue.insert(value, value);
            rbt.insert(value);

            std::cout << "Inserted value: " << value << " into all ADTs.\n";
        } catch (const std::exception& e) {
            std::cerr << "Error reading value from file: " << e.what() << "\n";
        }
    }
    done = true;
    std::cout << "File loaded and data inserted into all ADTs.\n";
}

// Mock function to select a file
std::string browseFile() {
    return "sample.txt";  // Replace this with actual file browsing logic if needed
}

// View and display the current ADT state
void viewADT(ADTType currentADT, Heap& heap, BST& bst, AVL& avl, BTree& btree, RedBlackTree& rbt,
             Stack& stack, Queue& queue, PriorityQueue& priorityQueue,
             const std::vector<int>& data, sf::RenderWindow& window, const sf::Font& font) {
    window.clear();

    sf::Text title("Viewing ADT", font, 30);
    title.setPosition(100, 20);
    title.setFillColor(sf::Color::White);
    window.draw(title);

    // Call the draw method from the selected ADT class
    switch (currentADT) {
        case ADTType::HEAP: heap.draw(window, font); break;
        case ADTType::AVL: avl.draw(window, font); break;
        case ADTType::STACK: stack.draw(window, font); break;
        case ADTType::QUEUE: queue.draw(window, font); break;
        case ADTType::BTREE: btree.draw(window, font); break;
        case ADTType::PRIORITY_QUEUE: priorityQueue.draw(window, font); break;
        case ADTType::RED_BLACK_TREE: rbt.draw(window, font); break;
        case ADTType::BST: bst.draw(window, font); break;
    }

    sf::Text backText("Press Backspace to return", font, 20);
    backText.setPosition(100, window.getSize().y - 50);
    backText.setFillColor(sf::Color::Yellow);
    window.draw(backText);

    window.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML ADT Menu");

    sf::Font font;
    if (!font.loadFromFile("edosz.ttf")) {
        std::cerr << "Failed to load font!\n";
        return -1;
    }

    AppState appState = AppState::MAIN_MENU;
    Menu mainMenu(window.getSize().x, window.getSize().y, {"Select ADT", "Insert", "Delete", "Search", "View ADT", "Import from File"}, font);
    Menu adtMenu(window.getSize().x, window.getSize().y, {"Heap", "BST", "AVL", "BTree", "Stack", "Queue", "Priority Queue", "Red-Black Tree"}, font);
    Menu operationMenu(window.getSize().x, window.getSize().y, {"Insert", "Delete", "Search", "View"}, font);

    ADTType currentADT = ADTType::HEAP;

    Heap heap;
    BST bst;
    AVL avl;
    BTree btree(3);  // Create a BTree with a degree of 3
    RedBlackTree rbt;
    Stack stack;
    Queue queue;
    PriorityQueue priorityQueue;

    std::vector<int> data;
    std::atomic<bool> done(false);
    std::thread fileThread;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                switch (appState) {
                    case AppState::MAIN_MENU:
                        if (event.key.code == sf::Keyboard::Up) mainMenu.moveUp();
                        if (event.key.code == sf::Keyboard::Down) mainMenu.moveDown();
                        if (event.key.code == sf::Keyboard::Enter) {
                            int selectedOption = mainMenu.getSelectedItemIndex();
                            if (selectedOption == 0) appState = AppState::ADT_SELECTION;
                            else if (selectedOption == 4) appState = AppState::VIEW_ADT;
                            else if (selectedOption == 5) {
                                std::string fileName = browseFile();
                                done = false;
                                fileThread = std::thread(loadDataFromFile, fileName, std::ref(data), std::ref(done),
                                                         currentADT, std::ref(heap), std::ref(bst), std::ref(avl),
                                                         std::ref(stack), std::ref(queue), std::ref(btree),
                                                         std::ref(priorityQueue), std::ref(rbt));
                            }
                        }
                        break;

                    case AppState::ADT_SELECTION:
                        if (event.key.code == sf::Keyboard::Up) adtMenu.moveUp();
                        if (event.key.code == sf::Keyboard::Down) adtMenu.moveDown();
                        if (event.key.code == sf::Keyboard::Enter) {
                            currentADT = static_cast<ADTType>(adtMenu.getSelectedItemIndex());
                            appState = AppState::ADT_OPERATIONS;
                        }
                        break;

                    case AppState::ADT_OPERATIONS:
                        if (event.key.code == sf::Keyboard::Up) operationMenu.moveUp();
                        if (event.key.code == sf::Keyboard::Down) operationMenu.moveDown();
                        if (event.key.code == sf::Keyboard::Enter) {
                            int option = operationMenu.getSelectedItemIndex();
                            if (option == 3) appState = AppState::VIEW_ADT;
                        }
                        break;

                    case AppState::VIEW_ADT:
                        if (event.key.code == sf::Keyboard::BackSpace) appState = AppState::MAIN_MENU;
                        break;
                }
            }
        }

        if (fileThread.joinable() && done) fileThread.join();

        window.clear();
        switch (appState) {
            case AppState::MAIN_MENU: mainMenu.draw(window); break;
            case AppState::ADT_SELECTION: adtMenu.draw(window); break;
            case AppState::ADT_OPERATIONS: operationMenu.draw(window); break;
            case AppState::VIEW_ADT: viewADT(currentADT, heap, bst, avl, btree, rbt, stack, queue, priorityQueue, data, window, font); break;
        }
        window.display();
    }

    return 0;
}
