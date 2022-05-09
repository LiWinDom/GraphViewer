#pragma once
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <vector>

#include "../Containers.h"
#include "../FormulaTree.h"

class GraphDrawer
{
public:
	GraphDrawer(const int16_t& x, const int16_t& y, const uint16_t& width, const uint16_t& height);

	uint8_t addGraph(const FormulaTree& tree, const uint32_t& color);

	void changeGraph(const uint8_t& index, const FormulaTree& tree);

	void changeColor(const uint8_t& index, const uint32_t& color);

	void eventProcessing(const sf::Event& event, const sf::Vector2i& mousePos);

	void draw(sf::RenderWindow& window);

private:
	int16_t x, y;
	uint16_t width, height;

	struct Graph {
		Graph(const FormulaTree& tree, const uint32_t& color) {
			this->color = color;
			this->tree = tree;
			return;
		}

		double calc(const double& x) {
			return this->tree.calc(x);
		}

		uint32_t color;
		FormulaTree tree;
	};

	std::vector<Graph*> graphs;

	void drawGraph(sf::RenderWindow& window, Graph* graph);
};