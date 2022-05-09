#pragma once
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <vector>

#include "../Config.h"

class TextField {
public:
    TextField(const int16_t& x, const int16_t& y, const uint16_t& width, const uint16_t& height, const sf::Font& font);

    std::string getText();

    void addChangeCallback(void (*callback)());

    void addEnterCallback(void (*callback)());

    void draw(sf::RenderWindow& window);

    void eventProcessing(const sf::Event& event, const sf::Vector2i& mousePos);

    void active();

    void deactive();

private:
    int16_t x, y;
    uint16_t width, height;
    std::string text = "";
    std::string mouseButton = "none";

    bool selected = false;
    sf::RectangleShape border;
    sf::Text textText;

    std::vector<void (*)()> changeCallbacks = {}, enterCallbacks = {};
};