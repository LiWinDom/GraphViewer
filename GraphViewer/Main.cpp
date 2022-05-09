#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#include "Config.h"
#include "Containers.h"
#include "Elements.h"
#include "FormulaTree.h"

sf::Font font;
std::vector<CheckBox*> checkboxes = {};
std::vector<TextField*> textfields = {};

FormulaTree testTree;
sf::Text text;

void onStart(sf::RenderWindow& window) {
    font.loadFromFile("resourses/Consolas.ttf");
    //sf::Image icon;
    //icon.loadFromFile("resourses/icon.png");
    //window.setIcon(52, 52, icon.getPixelsPtr());
    window.setVerticalSyncEnabled(true);

    text.setCharacterSize(TEXT_SIZE);
    text.setFillColor(sf::Color(SELECTED_COLOR));
    text.setPosition(30, 30);
    text.setFont(font);
    text.setString("Ready");

    textfields.push_back(new TextField(30, 80, TEXT_SIZE * 20, TEXT_SIZE * 1.5, font));
    textfields.push_back(new TextField(TEXT_SIZE * 20 + PADDING_SIZE + 30, 80, TEXT_SIZE * 5, TEXT_SIZE * 1.5, font));
    textfields[0]->addChangeCallback([]() -> void {
        try {
            testTree.convertPolynom(textfields[0]->getText());
            text.setString("OK");
        }
        catch (Error err) {
            text.setString(err.source + ": " + err.message);
        }
    });
    textfields[0]->addEnterCallback([]() -> void {
        try {
            if (textfields[1]->getText() != "") {
                text.setString(std::to_string(testTree.count(std::stod(textfields[1]->getText()))));
            }
            else {
                text.setString(std::to_string(testTree.count(0)));
            }
        }
        catch (Error err) {
            text.setString(err.source + ": " + err.message);
        }
    });
    
    return;
}

void display(sf::RenderWindow& window) {
    window.clear(sf::Color(BACKGROUND_COLOR));

    for (uint8_t i = 0; i < checkboxes.size(); ++i) {
        checkboxes[i]->draw(window);
    }
    for (uint8_t i = 0; i < textfields.size(); ++i) {
        textfields[i]->draw(window);
    }
    window.draw(text);

    window.display();
    return;
}

void eventProcessing(sf::RenderWindow& window) {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        for (uint8_t i = 0; i < checkboxes.size(); ++i) {
            checkboxes[i]->eventProcessing(event, mousePos);
        }
        for (uint8_t i = 0; i < textfields.size(); ++i) {
            textfields[i]->eventProcessing(event, mousePos);
        }
    }
    return;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Graph Viewer [0.32]", sf::Style::Close);
    onStart(window);

    while (window.isOpen()) {
        eventProcessing(window);
        display(window);
    }
    return 0;
}