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

void GraphDrawer::showGraph(const uint8_t& index) {
	if (index >= this->graphs.size()) {
		throw Error("GraphDrawer", "No graph with index \"" + std::to_string(index) + "\"");
	}
	this->graphs[index]->show = true;
	return;
}

void GraphDrawer::hideGraph(const uint8_t& index) {
	if (index >= this->graphs.size()) {
		throw Error("GraphDrawer", "No graph with index \"" + std::to_string(index) + "\"");
	}
	this->graphs[index]->show = false;
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
	if (!graph->show) return;

	try {
		graph->calc(0);
	}
	catch (Error err) {
		return;
	}

	sf::Vector2f lastPoint;
	for (int16_t i = this->x; i < this->x + this->width; ++i) {
		int16_t j = this->height / 2.0 - graph->calc((i - this->width / 2.0) / 100.0) * 100;

		if (i > this->x) {
			if (j > this->y && j < this->y + this->height && lastPoint.y > this->y && lastPoint.y < this->y + this->height) {
				sf::VertexArray line(sf::LinesStrip, 2);
				line[0].position = lastPoint;
				line[1].position = sf::Vector2f(i, j);
				line[0].color = sf::Color(graph->color);
				line[1].color = sf::Color(graph->color);

				window.draw(line);
			}
		}
		lastPoint = sf::Vector2f(i, j);
	}
	return;
}