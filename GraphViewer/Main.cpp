#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#include "CheckBox.h"
#include "Config.h"
#include "Containers.h"

sf::Font font;
std::vector<CheckBox*> checkboxes = {};
CheckBox* f1, *f2, *f3;

void onStart(sf::RenderWindow& window) {
    font.loadFromFile("resourses/Consolas.ttf");

    f1 = new CheckBox(30, 30, TEXT_SIZE * 1.5, TEXT_SIZE * 1.5, 0xC00000FF);
    f1->setLabel("f1", font);
    f2 = new CheckBox(30, 30 + TEXT_SIZE * 1.5 + PADDING_SIZE, TEXT_SIZE * 1.5, TEXT_SIZE * 1.5, 0x00C000FF);
    f2->setLabel("f2", font);
    f3 = new CheckBox(30, 30 + TEXT_SIZE * 3 + PADDING_SIZE * 2, TEXT_SIZE * 1.5, TEXT_SIZE * 1.5, 0x0000C0FF);
    f3->setLabel("f3", font);
    checkboxes = { f1, f2, f3 };
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
    for (uint8_t i = 0; i < checkboxes.size(); ++i) {
        checkboxes[i]->eventProcessing(mousePos);
    }
    return;
}

void eventProcessing(sf::RenderWindow& window) {
    sf::Event event;
    static std::string mouseButton = "none";
    static sf::Vector2i lastMousePos;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (mouseButton == "none" || mouseButton == "left" || mouseButton == "leftMove")) {
            if (mouseButton == "none") {
                mouseButton = "left";
            }
            else if (lastMousePos - sf::Mouse::getPosition() != sf::Vector2i(0, 0)) {
                mouseButton = "leftMove";
            }
            lastMousePos = sf::Mouse::getPosition();
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && mouseButton == "none") {
            mouseButton = "right";
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (mouseButton == "left") {
                clickEvent(mousePos);
            }
            mouseButton = "none";
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