#pragma once
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Containers.h"
#include "Config.h"

class Button {
public:
    Button(const Position& position, const Size& size, const TextInfo& text, void (*onClick)());

    void draw(sf::RenderWindow& window);

    void eventProcessing(const sf::RenderWindow& window);

private:
    Position position;
    Size size;
    TextInfo textInfo;

    uint8_t selected = 0;
    sf::RectangleShape border;
    sf::Text text;

    void (*onClick)();
};