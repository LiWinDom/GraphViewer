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

	void showGraph(const uint8_t& index);

	void hideGraph(const uint8_t& index);

	void eventProcessing(const sf::Event& event, const sf::Vector2i& mousePos);

	void draw(sf::RenderWindow& window);

private:
	int16_t x, y;
	uint16_t width, height;

	sf::Vector2f needShift = sf::Vector2f(0, 0), shift = sf::Vector2f(0, 0);
	double scale = 100;
	std::string mouseButton = "none";
	sf::Vector2i lastMousePos;

	struct Graph {
		Graph(const FormulaTree& tree, const uint32_t& color, const bool& show = true) {
			this->color = color;
			this->tree = tree;
			this->show = show;
			return;
		}

		double calc(const double& x) {
			return this->tree.calc(x);
		}

		FormulaTree tree;
		uint32_t color;
		bool show;
	};

	std::vector<Graph*> graphs;

	sf::Vector2i coordinateToPoint(const sf::Vector2f& coordinate);

	sf::Vector2f pointToCoordinate(const sf::Vector2i& point);

	void drawPrimaryLines(sf::RenderWindow& window);

	void drawSecondaryLines(sf::RenderWindow& window);

	void drawGraph(sf::RenderWindow& window, Graph* graph);
};
