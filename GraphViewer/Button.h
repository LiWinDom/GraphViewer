#pragma once
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Config.h"
#include "Containers.h"

class Button {
public:
    Button(const int16_t& x, const int16_t& y, const uint16_t& width, const uint16_t& height, const std::string& label, const sf::Font& font, void (*onClick)());

    void draw(sf::RenderWindow& window);

    void eventProcessing(const sf::RenderWindow& window);

private:
    int16_t x, y;
    uint16_t width, height;
    std::string label;

    uint8_t selected = 0;
    sf::RectangleShape border;
    sf::Text text;

    void (*onClick)();
};