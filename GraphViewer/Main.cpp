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

GraphDrawer drawer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
FormulaTree test;

void onStart(sf::RenderWindow& window) {
    font.loadFromFile("resourses/Consolas.ttf");
    //sf::Image icon;
    //icon.loadFromFile("resourses/icon.png");
    //window.setIcon(52, 52, icon.getPixelsPtr());
    window.setVerticalSyncEnabled(true);

    textfields.push_back(new TextField(WINDOW_WIDTH - 320 - PADDING_SIZE, PADDING_SIZE, 320, TEXT_SIZE * 1.5, font));
    checkboxes.push_back(new CheckBox(WINDOW_WIDTH - 320 - 2 * PADDING_SIZE - TEXT_SIZE * 1.5, PADDING_SIZE, TEXT_SIZE * 1.5, TEXT_SIZE * 1.5, 0xC00000FF));
    checkboxes[0]->setLabel("f1", font);
    checkboxes[0]->click();
    textfields.push_back(new TextField(WINDOW_WIDTH - 320 - PADDING_SIZE, 2 * PADDING_SIZE + TEXT_SIZE * 1.5, 320, TEXT_SIZE * 1.5, font));
    checkboxes.push_back(new CheckBox(WINDOW_WIDTH - 320 - 2 * PADDING_SIZE - TEXT_SIZE * 1.5, 2 * PADDING_SIZE + TEXT_SIZE * 1.5, TEXT_SIZE * 1.5, TEXT_SIZE * 1.5, 0xC0C000FF));
    checkboxes[1]->setLabel("f2", font);
    checkboxes[1]->click();
    textfields.push_back(new TextField(WINDOW_WIDTH - 320 - PADDING_SIZE, 3 * PADDING_SIZE + TEXT_SIZE * 3, 320, TEXT_SIZE * 1.5, font));
    checkboxes.push_back(new CheckBox(WINDOW_WIDTH - 320 - 2 * PADDING_SIZE - TEXT_SIZE * 1.5, 3 * PADDING_SIZE + TEXT_SIZE * 3, TEXT_SIZE * 1.5, TEXT_SIZE * 1.5, 0x00C000FF));
    checkboxes[2]->setLabel("f3", font);
    checkboxes[2]->click();
    textfields.push_back(new TextField(WINDOW_WIDTH - 320 - PADDING_SIZE, 4 * PADDING_SIZE + TEXT_SIZE * 4.5, 320, TEXT_SIZE * 1.5, font));
    checkboxes.push_back(new CheckBox(WINDOW_WIDTH - 320 - 2 * PADDING_SIZE - TEXT_SIZE * 1.5, 4 * PADDING_SIZE + TEXT_SIZE * 4.5, TEXT_SIZE * 1.5, TEXT_SIZE * 1.5, 0x00C0C0FF));
    checkboxes[3]->setLabel("f4", font);
    checkboxes[3]->click();
    textfields.push_back(new TextField(WINDOW_WIDTH - 320 - PADDING_SIZE, 5 * PADDING_SIZE + TEXT_SIZE * 6, 320, TEXT_SIZE * 1.5, font));
    checkboxes.push_back(new CheckBox(WINDOW_WIDTH - 320 - 2 * PADDING_SIZE - TEXT_SIZE * 1.5, 5 * PADDING_SIZE + TEXT_SIZE * 6, TEXT_SIZE * 1.5, TEXT_SIZE * 1.5, 0x0000C0FF));
    checkboxes[4]->setLabel("f5", font);
    checkboxes[4]->click();
    textfields.push_back(new TextField(WINDOW_WIDTH - 320 - PADDING_SIZE, 6 * PADDING_SIZE + TEXT_SIZE * 7.5, 320, TEXT_SIZE * 1.5, font));
    checkboxes.push_back(new CheckBox(WINDOW_WIDTH - 320 - 2 * PADDING_SIZE - TEXT_SIZE * 1.5, 6 * PADDING_SIZE + TEXT_SIZE * 7.5, TEXT_SIZE * 1.5, TEXT_SIZE * 1.5, 0xC000C0FF));
    checkboxes[5]->setLabel("f6", font);
    checkboxes[5]->click();

    test.convertPolynom("sin(x + t)");
    drawer.addGraph(test, 0xC00000FF);
    
    return;
}

void display(sf::RenderWindow& window) {
    window.clear(sf::Color(BACKGROUND_COLOR));

    drawer.draw(window);
    for (uint8_t i = 0; i < checkboxes.size(); ++i) {
        checkboxes[i]->draw(window);
    }
    for (uint8_t i = 0; i < textfields.size(); ++i) {
        textfields[i]->draw(window);
    }

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