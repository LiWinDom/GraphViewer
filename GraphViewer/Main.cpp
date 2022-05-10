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

void createCallbacks() {
    textfields[0]->addChangeCallback([](const std::string& text) ->
        void {
            FormulaTree tree;
            try {
                std::transform(text.begin(), text.end(), text.begin(),
                    [](unsigned char c) { return std::tolower(c); });
                tree.convertPolynom(text);
            }
            catch (Error err) {}
            drawer.changeGraph(0, tree);
            return;
        }
    );
    textfields[1]->addChangeCallback([](const std::string& text) ->
        void {
            FormulaTree tree;
            try {
                std::transform(text.begin(), text.end(), text.begin(),
                    [](unsigned char c) { return std::tolower(c); });
                tree.convertPolynom(text);
            }
            catch (Error err) {}
            drawer.changeGraph(1, tree);
            return;
        }
    );
    textfields[2]->addChangeCallback([](const std::string& text) ->
        void {
            FormulaTree tree;
            try {
                std::transform(text.begin(), text.end(), text.begin(),
                    [](unsigned char c) { return std::tolower(c); });
                tree.convertPolynom(text);
            }
            catch (Error err) {}
            drawer.changeGraph(2, tree);
            return;
        }
    );
    textfields[3]->addChangeCallback([](const std::string& text) ->
        void {
            FormulaTree tree;
            try {
                std::transform(text.begin(), text.end(), text.begin(),
                    [](unsigned char c) { return std::tolower(c); });
                tree.convertPolynom(text);
            }
            catch (Error err) {}
            drawer.changeGraph(3, tree);
            return;
        }
    );
    textfields[4]->addChangeCallback([](const std::string& text) ->
        void {
            FormulaTree tree;
            try {
                std::transform(text.begin(), text.end(), text.begin(),
                    [](unsigned char c) { return std::tolower(c); });
                tree.convertPolynom(text);
            }
            catch (Error err) {}
            drawer.changeGraph(4, tree);
            return;
        }
    );
    textfields[5]->addChangeCallback([](const std::string& text) ->
        void {
            FormulaTree tree;
            try {
                std::transform(text.begin(), text.end(), text.begin(),
                    [](unsigned char c) { return std::tolower(c); });
                tree.convertPolynom(text);
            }
            catch (Error err) {}
            drawer.changeGraph(5, tree);
            return;
        }
    );

    checkboxes[0]->addCallback([](const bool& selected) ->
        void {
            if (selected) drawer.showGraph(0);
            else drawer.hideGraph(0);
            return;
        }
    );
    checkboxes[1]->addCallback([](const bool& selected) ->
        void {
            if (selected) drawer.showGraph(1);
            else drawer.hideGraph(1);
            return;
        }
    );
    checkboxes[2]->addCallback([](const bool& selected) ->
        void {
            if (selected) drawer.showGraph(2);
            else drawer.hideGraph(2);
            return;
        }
    );
    checkboxes[3]->addCallback([](const bool& selected) ->
        void {
            if (selected) drawer.showGraph(3);
            else drawer.hideGraph(3);
            return;
        }
    );
    checkboxes[4]->addCallback([](const bool& selected) ->
        void {
            if (selected) drawer.showGraph(4);
            else drawer.hideGraph(4);
            return;
        }
    );
    checkboxes[5]->addCallback([](const bool& selected) ->
        void {
            if (selected) drawer.showGraph(5);
            else drawer.hideGraph(5);
            return;
        }
    );
    return;
}

void onStart(sf::RenderWindow& window) {
    font.loadFromFile("resourses/Consolas.ttf");
    //sf::Image icon;
    //icon.loadFromFile("resourses/icon.png");
    //window.setIcon(52, 52, icon.getPixelsPtr());
    window.setVerticalSyncEnabled(true);

    uint32_t colors[6] = {0xC00000FF, 0xC0C000FF, 0x00C000FF, 0x00C0C0FF, 0x0000C0FF, 0xC000C0FF};
    FormulaTree buf;
    for (uint8_t i = 0; i < 6; ++i) {
        textfields.push_back(new TextField(WINDOW_WIDTH - 320 - PADDING_SIZE, PADDING_SIZE * (i + 1) + TEXT_SIZE * 1.5 * i,
            320, TEXT_SIZE * 1.5, font));
        checkboxes.push_back(new CheckBox(WINDOW_WIDTH - 320 - 2 * PADDING_SIZE - TEXT_SIZE * 1.5, PADDING_SIZE * (i + 1) + TEXT_SIZE * 1.5 * i,
            TEXT_SIZE * 1.5, TEXT_SIZE * 1.5, colors[i]));
        checkboxes[i]->setLabel("f" + std::to_string(i + 1), font);
        checkboxes[i]->click();

        drawer.addGraph(buf, colors[i]);
    }
    createCallbacks();
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
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Graph Viewer [1.22]", sf::Style::Close);
    onStart(window);

    while (window.isOpen()) {
        eventProcessing(window);
        display(window);
    }
    return 0;
}