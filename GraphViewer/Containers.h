#pragma once
#include <string>
#include <SFML/Graphics.hpp>

#include "Config.h"

struct Error {
	std::string source = "";
	std::string message = "";

	Error(const std::string& source, const std::string& message) {
		this->source = source;
		this->message = message;
		return;
	}
};

struct Position {
	uint16_t x, y;

	Position(const uint16_t& x, const uint16_t& y) {
		this->x = x;
		this->y = y;
		return;
	}
};

struct Size {
	uint16_t width, height;

	Size(const uint16_t& width, const uint16_t& height) {
		this->width = width;
		this->height = height;
		return;
	}
};

struct TextInfo {
	std::string text;
	sf::Font font;
	float textSize;

	TextInfo(const std::string& text, const sf::Font& font, const float& textSize = TEXT_SIZE) {
		this->text = text;
		this->font = font;
		this->textSize = textSize;
		return;
	}
};
