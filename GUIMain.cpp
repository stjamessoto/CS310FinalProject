//GUIMain.cpp
#include "GUIManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// Helper function to read integers from a file
std::vector<int> readFromFile(const std::string& filename) {
    std::vector<int> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int value;
        while (iss >> value) {
            data.push_back(value);
        }
    }

    file.close();
    return data;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Menu with ADTs");
    GUIManager guiManager(window); // Use the GUIManager for handling ADTs and their visualization

    // Read data from sample.txt and load it into the default ADT
    const std::string filename = "sample.txt";
    std::vector<int> initialData = readFromFile(filename);

    if (!initialData.empty()) {
        std::cout << "Loaded data from " << filename << ": ";
        for (int value : initialData) {
            std::cout << value << " ";
        }
        std::cout << "\n";

        // Load data into the initial ADT (default is Heap in this example)
        guiManager.loadInitialData(initialData);
    } else {
        std::cout << "No data loaded from " << filename << ".\n";
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Let GUIManager handle the event
            guiManager.processEvent(event);
        }

        // Render the GUI and ADT visuals
        guiManager.render();
    }

    return 0;
}
