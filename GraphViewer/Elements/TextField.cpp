#include "TextField.h"

TextField::TextField(const int16_t& x, const int16_t& y, const uint16_t& width, const uint16_t& height, const uint32_t& selectedColor) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->selectedColor = selectedColor;

    this->border.setFillColor(sf::Color(BACKGROUND_COLOR));
    this->border.setOutlineColor(sf::Color(this->selectedColor));
    this->border.setOutlineThickness(BORDER_SIZE);
    this->border.setSize(sf::Vector2f(this->width - 2 * BORDER_SIZE, this->height - 2 * BORDER_SIZE));
    this->border.setPosition(this->x + BORDER_SIZE, this->y + BORDER_SIZE);

    this->text.setCharacterSize(TEXT_SIZE);
    this->text.setPosition(this->x + this->width / 2, this->y + this->height / 2);
    this->text.setFillColor(sf::Color(this->selectedColor));

    return;
}

void TextField::addChangeCallback(void (*callback)()) {
    this->changeCallbacks.push_back(callback);
    return;
}

void TextField::addEnterCallback(void (*callback)()) {
    this->enterCallbacks.push_back(callback);
    return;
}

void TextField::draw(sf::RenderWindow& window) {
    window.draw(border);
    window.draw(text);

    return;
}

void TextField::eventProcessing(const sf::Event& event, const sf::Vector2i& mousePos) {
    static std::string mouseButton = "none";

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseButton == "none") {
        if (mousePos.x >= this->x && mousePos.x <= this->x + this->width &&
            mousePos.y >= this->y && mousePos.y <= this->y + this->height) {
            mouseButton = "left";
        }
        else {
            mouseButton = "missed";
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && mouseButton == "none") {
        mouseButton = "right";
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (mouseButton == "left") {
            if (mousePos.x >= this->x && mousePos.x <= this->x + this->width &&
                mousePos.y >= this->y && mousePos.y <= this->y + this->height) {
                this->click();
            }
        }
        mouseButton = "none";
    }
    return;
}

void TextField::click() {
    this->selected = !this->selected;
    if (this->selected) {
        this->border.setFillColor(sf::Color(this->selectedColor));
        this->text.setFillColor(sf::Color(BACKGROUND_COLOR));
    }
    else {
        this->border.setFillColor(sf::Color(BACKGROUND_COLOR));
        this->text.setFillColor(sf::Color(this->selectedColor));
    }

    for (uint8_t i = 0; i < callbacks.size(); ++i) {
        callbacks[i](this->selected);
    }
    return;
}