#include "CheckBox.h"

CheckBox::CheckBox(const int16_t& x, const int16_t& y, const uint16_t& width, const uint16_t& height, const uint32_t& selectedColor) {
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

void CheckBox::setLabel(const std::string& label, const sf::Font& font) {
    this->text.setFont(font);
    this->text.setString(label);
    sf::FloatRect bounds = this->text.getLocalBounds();
    this->text.setOrigin(bounds.width / 2.0, TEXT_SIZE / 1.5);

    return;
}

void CheckBox::addCallback(void (*callback)(const bool&)) {
    this->callbacks.push_back(callback);
}

void CheckBox::draw(sf::RenderWindow& window) {
    window.draw(border);
    window.draw(text);

    return;
}

void CheckBox::eventProcessing(const sf::Vector2i& mousePos) {
    if (mousePos.x >= this->x && mousePos.x <= this->x + this->width && mousePos.y >= this->y && mousePos.y <= this->y + this->height) {
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
    }
    return;
}