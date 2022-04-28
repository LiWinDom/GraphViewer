#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#include "Button.h"
#include "Config.h"
#include "Containers.h"

sf::Font font;
std::vector<Button*> buttons = {};
Button* AVLButton;

void onStart(sf::RenderWindow& window) {
    font.loadFromFile("resourses/Consolas.ttf");

    AVLButton = new Button(20, 20, TEXT_SIZE * 5, TEXT_SIZE, "Test", font, []() -> void {});
    buttons = { AVLButton };
    //sf::Image icon;
    //icon.loadFromFile("resourses/icon.png");
    //window.setIcon(52, 52, icon.getPixelsPtr());
    window.setVerticalSyncEnabled(true);

    return;
}

void display(sf::RenderWindow& window) {
    window.clear(sf::Color(BACKGROUND_COLOR));

    for (uint8_t i = 0; i < buttons.size(); ++i) {
        buttons[i]->draw(window);
    }
    window.display();

    return;
}

void clickEvent(sf::RenderWindow& window, uint16_t x, uint16_t y) {
    
    return;
}

void eventProcessing(sf::RenderWindow& window) {
    sf::Event event;
    static std::string mouseButton = "none";
    static sf::Vector2i lastMousePos;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        for (uint8_t i = 0; i < buttons.size(); ++i) {
            buttons[i]->eventProcessing(window);
        }
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
                clickEvent(window, mousePos.x, mousePos.y);
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