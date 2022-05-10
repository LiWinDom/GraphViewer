#pragma once
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <vector>

#include "../Config.h"

class TextField {
public:
    TextField(const int16_t& x, const int16_t& y, const uint16_t& width, const uint16_t& height, const sf::Font& font);

    std::string getText();

    void active();

    void deactive();

    void addChangeCallback(void (*callback)(const std::string& text));

    void addEnterCallback(void (*callback)(const std::string& text));

    void eventProcessing(const sf::Event& event, const sf::Vector2i& mousePos);

    void draw(sf::RenderWindow& window);

private:
    int16_t x, y;
    uint16_t width, height;
    std::string text = "";
    std::string mouseButton = "none";

    bool selected = false;
    sf::RectangleShape border;
    sf::Text textText;

    std::vector<void (*)(const std::string& text)> changeCallbacks = {}, enterCallbacks = {};
};