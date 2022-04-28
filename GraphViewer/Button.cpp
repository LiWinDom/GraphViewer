#include "Button.h"

Button::Button(const int16_t& x, const int16_t& y, const uint16_t& width, const uint16_t& height, const std::string& label, const sf::Font& font, void (*onClick)()) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->label = label;
    this->onClick = onClick;

    this->border.setOutlineThickness(BORDER_SIZE);
    this->border.setFillColor(sf::Color(BACKGROUND_COLOR));
    this->border.setSize(sf::Vector2f(this->width - 2 * BORDER_SIZE, this->height - 2 * BORDER_SIZE));
    this->border.setPosition(this->x + BORDER_SIZE, this->y + BORDER_SIZE);

    this->text.setFont(font);
    this->text.setCharacterSize(TEXT_SIZE);
    this->text.setString(this->label);
    sf::FloatRect bounds = this->text.getLocalBounds();
    this->text.setOrigin(bounds.width / 2.0, TEXT_SIZE / 1.5);
    this->text.setPosition(this->x + this->width / 2, this->y + this->height / 2);

    return;
}

void Button::draw(sf::RenderWindow& window) {
    switch (selected) {
    case 0:
        this->border.setOutlineColor(sf::Color(INACTIVE_COLOR));
        this->text.setFillColor(sf::Color(INACTIVE_COLOR));
        break;
    case 1:
        this->border.setOutlineColor(sf::Color(HOVER_COLOR));
        this->text.setFillColor(sf::Color(HOVER_COLOR));
        break;
    case 2:
        this->border.setOutlineColor(sf::Color(SELECTED_COLOR));
        this->text.setFillColor(sf::Color(SELECTED_COLOR));
        break;
    }
    window.draw(border);
    window.draw(text);

    return;
}

void Button::eventProcessing(const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (mousePos.x >= this->x && mousePos.y <= this->x + this->width && mousePos.y >= this->y && mousePos.y <= this->y + this->height) {
        if (this->selected != 2) this->selected = 1;
        return;
    }
    if (this->selected != 2) this->selected = 0;
    return;
}