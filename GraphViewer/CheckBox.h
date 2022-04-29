#pragma once
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Config.h"
#include "Containers.h"

class CheckBox {
public:
    CheckBox(const int16_t& x, const int16_t& y, const uint16_t& width, const uint16_t& height, const uint32_t& selectedColor = SELECTED_COLOR);

    void setLabel(const std::string& label, const sf::Font& font);

    void addCallback(void (*callback)(const bool&));

    void draw(sf::RenderWindow& window);

    void eventProcessing(const sf::Vector2i& mousePos);

private:
    int16_t x, y;
    uint16_t width, height;
    uint32_t selectedColor;

    bool selected = false;
    sf::RectangleShape border;
    sf::Text text;

    std::vector<void (*)(const bool&)> callbacks = {};
};