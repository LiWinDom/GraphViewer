#include "GraphDrawer.h"

GraphDrawer::GraphDrawer(const int16_t& x, const int16_t& y, const uint16_t& width, const uint16_t& height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	return;
}

uint8_t GraphDrawer::addGraph(const FormulaTree& tree, const uint32_t& color) {
	this->graphs.push_back(new Graph(tree, color));
	return this->graphs.size() - 1;
}

void GraphDrawer::changeGraph(const uint8_t& index, const FormulaTree& tree) {
	if (index >= this->graphs.size()) {
		throw Error("GraphDrawer", "No graph with index \"" + std::to_string(index) + "\"");
	}
	this->graphs[index]->tree = tree;
	return;
}

void GraphDrawer::changeColor(const uint8_t& index, const uint32_t& color) {
	if (index >= this->graphs.size()) {
		throw Error("GraphDrawer", "No graph with index \"" + std::to_string(index) + "\"");
	}
	this->graphs[index]->color = color;
	return;
}

void GraphDrawer::eventProcessing(const sf::Event& event, const sf::Vector2i& mousePos) {
	return;
}

void GraphDrawer::draw(sf::RenderWindow& window) {
	for (uint8_t i = 0; i < this->graphs.size(); ++i) {
		this->drawGraph(window, this->graphs[i]);
	}
	return;
}

void GraphDrawer::drawGraph(sf::RenderWindow& window, Graph* graph) {
	try {
		graph->calc(0);
	}
	catch (Error err) {
		return;
	}

	for (int16_t i = this->x; i < this->x + this->width; ++i) {
		int16_t j = this->height / 2.0 - graph->calc((i - this->width / 2.0) / 100.0) * 100;
		if (j < this->y || j > this->y + this->height) continue;

		sf::RectangleShape rect;
		rect.setFillColor(sf::Color(graph->color));
		rect.setPosition(i, j);
		rect.setSize(sf::Vector2f(1, 1));

		window.draw(rect);
	}
	return;
}