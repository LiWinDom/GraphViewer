#include "Button.h"

Button::Button(const Position& position, const Size& size, const TextInfo& text, void (*onClick)()) {
    this->position = position;
    this->size = size;
    this->textInfo = textInfo;

    this->text.setFont(this->textInfo.font);
    this->text.setCharacterSize(this->textInfo.textSize);
    this->text.setString(this->textInfo.text);
    sf::FloatRect bounds = this->text.getLocalBounds();
    this->text.setOrigin(bounds.width / 2.0, TEXT_SIZE / 1.75);
    this->text.setPosition(x + PADDING_SIZE + (text.size() * TEXT_SIZE / 4.0), y);
    return;
}

void Button::draw(sf::RenderWindow& window) {
    this->border.setOutlineThickness(BORDER_SIZE);
    this->border.setFillColor(sf::Color(BACKGROUND_COLOR));
    this->border.setSize(sf::Vector2f(width - 2 * BORDER_SIZE, height - 2 * BORDER_SIZE));
    this->border.setPosition(x + BORDER_SIZE, y + BORDER_SIZE);

    switch (selected) {
    case 0:
        this->border.setOutlineColor(sf::Color(INACTIVE_COLOR));
        this->textText.setFillColor(sf::Color(INACTIVE_COLOR));
        break;
    case 1:
        this->border.setOutlineColor(sf::Color(HOVER_COLOR));
        this->textText.setFillColor(sf::Color(HOVER_COLOR));
        break;
    case 2:
        this->border.setOutlineColor(sf::Color(SELECTED_COLOR));
        this->textText.setFillColor(sf::Color(SELECTED_COLOR));
        break;
    }

    window.draw(border);
    window.draw(textText);

    return;
}

bool Button::eventProcessing(const sf::RenderWindow window) {
    if (curX >= x && curX <= x + width && curY >= y && curY <= y + height) {
        if (this->selected != 2) this->selected = 1;
        return true;
    }
    if (this->selected != 2) this->selected = 0;
    return false;
}