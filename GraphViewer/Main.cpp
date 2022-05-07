#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#include "Config.h"
#include "Containers.h"
#include "Elements.h"

sf::Font font;
std::vector<CheckBox*> checkboxes = {};
std::vector<TextField*> textfields = {};

void onStart(sf::RenderWindow& window) {
    font.loadFromFile("resourses/Consolas.ttf");

    CheckBox* f1;
    f1 = new CheckBox(30, 30, TEXT_SIZE * 1.5, TEXT_SIZE * 1.5, 0xC00000FF);
    f1->setLabel("f1", font);
    checkboxes.push_back(f1);
    //sf::Image icon;
    //icon.loadFromFile("resourses/icon.png");
    //window.setIcon(52, 52, icon.getPixelsPtr());
    window.setVerticalSyncEnabled(true);

    return;
}

void display(sf::RenderWindow& window) {
    window.clear(sf::Color(BACKGROUND_COLOR));

    for (uint8_t i = 0; i < checkboxes.size(); ++i) {
        checkboxes[i]->draw(window);
    }
    window.display();

    return;
}

void clickEvent(const sf::Vector2i& mousePos) {
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
    }
    return;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Graph Viewer", sf::Style::Close);
    onStart(window);

    while (window.isOpen()) {
        eventProcessing(window);
        display(window);
    }
    return 0;
}