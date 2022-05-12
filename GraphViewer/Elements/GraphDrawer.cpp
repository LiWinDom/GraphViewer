#include "GraphDrawer.h"

GraphDrawer::GraphDrawer(const int16_t& x, const int16_t& y, const uint16_t& width, const uint16_t& height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	return;
}

void GraphDrawer::setFont(const sf::Font& font) {
	this->font = font;
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
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Up) {
			if (this->curPrecision < 4) ++this->curPrecision;
		}
		else if (event.key.code == sf::Keyboard::Down) {
			if (this->curPrecision > 0) --this->curPrecision;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (this->mouseButton == "none" || this->mouseButton == "left" || this->mouseButton == "leftMove")) {
		if (mouseButton == "none") {
			mouseButton = "left";
		}
		else if (this->lastMousePos != mousePos) {
			this->shift.x += (this->lastMousePos - mousePos).x / this->scale;
			this->shift.y += (this->lastMousePos - mousePos).y / this->scale;

			this->shift.x = std::max(std::min(this->shift.x, (float)32767), (float)-32768);
			this->shift.y = std::max(std::min(this->shift.y, (float)32767), (float)-32768);
			mouseButton = "leftMove";
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && (this->mouseButton == "none" || this->mouseButton == "right")) {
		this->mouseButton = "right";
	}
	else if (event.type == sf::Event::MouseButtonReleased) {
		this->mouseButton = "none";
	}
	else if (event.type == sf::Event::MouseWheelMoved) {
		if (event.mouseWheel.delta > 0 && this->scale < 1000) {
			this->scale += this->scale / 20;
		}
		else if (event.mouseWheel.delta < 0 && this->scale > 10) {
			this->scale -= this->scale / 20;
		}
	}
	this->lastMousePos = mousePos;
	return;
}

void GraphDrawer::draw(sf::RenderWindow& window) {
	this->drawLines(window);
	for (uint8_t i = 0; i < this->graphs.size(); ++i) {
		this->drawGraph(window, this->graphs[i]);
	}
	this->drawNumbers(window);

	return;
}

sf::Vector2f GraphDrawer::coordinateToPoint(const sf::Vector2f& coordinate) {
	return sf::Vector2f((coordinate.x - this->shift.x) * this->scale + this->width / 2.0 + this->x,
		(-coordinate.y - this->shift.y) * this->scale + this->height / 2.0 + this->y);
}

sf::Vector2f GraphDrawer::pointToCoordinate(const sf::Vector2f& point) {
	return sf::Vector2f((point.x - this->x - this->width / 2.0) / this->scale + this->shift.x,
		 -((point.y - this->y - this->height / 2.0) / this->scale + this->shift.y));
}

void GraphDrawer::drawLines(sf::RenderWindow& window) {
	double multiplier = 0.125;
	if (this->scale > 500) multiplier = 8;
	else if (this->scale > 250) multiplier = 4;
	else if (this->scale > 100) multiplier = 2;
	else if (this->scale > 50) multiplier = 1;
	else if (this->scale > 25) multiplier = 0.5;
	else if (this->scale > 15) multiplier = 0.25;

	double intpart;
	std::pair<double, double> xPrev, xCur, xNext;
	xPrev.second = std::modf(std::abs(this->pointToCoordinate(sf::Vector2f(this->x - 1, 0)).x) * multiplier, &intpart);
	xPrev.first = intpart;
	xCur.second = std::modf(std::abs(this->pointToCoordinate(sf::Vector2f(this->x, 0)).x) * multiplier, &intpart);
	xCur.first = intpart;
	for (int16_t j = this->x + 1; j <= this->x + this->width; ++j) {
		xNext.second = std::modf(std::abs(this->pointToCoordinate(sf::Vector2f(j, 0)).x) * multiplier, &intpart);
		xNext.first = intpart;

		if (xCur.second <= xPrev.second && xCur.second < xNext.second) {
			sf::VertexArray line(sf::LinesStrip, 2);
			line[0].position = sf::Vector2f(j - 1, this->y);
			line[1].position = sf::Vector2f(j - 1, this->y + this->height);

			if (xCur.first == 0) {
				line[0].color = sf::Color(0x202020FF);
				line[1].color = sf::Color(0x202020FF);
			}
			else {
				line[0].color = sf::Color(0xC0C0C0FF);
				line[1].color = sf::Color(0xC0C0C0FF);
			}
			window.draw(line);
		}
		xPrev = xCur;
		xCur = xNext;
	}

	std::pair<double, double> yPrev, yCur, yNext;
	yPrev.second = std::modf(std::abs(this->pointToCoordinate(sf::Vector2f(0, this->y - 1)).y) * multiplier, &intpart);
	yPrev.first = intpart;
	yCur.second = std::modf(std::abs(this->pointToCoordinate(sf::Vector2f(0, this->y)).y) * multiplier, &intpart);
	yCur.first = intpart;
	for (int16_t j = this->y + 1; j <= this->y + this->height; ++j) {
		yNext.second = std::modf(std::abs(this->pointToCoordinate(sf::Vector2f(0, j)).y) * multiplier, &intpart);
		yNext.first = intpart;

		if (yCur.second <= yPrev.second && yCur.second < yNext.second) {
			sf::VertexArray line(sf::LinesStrip, 2);
			line[0].position = sf::Vector2f(this->x, j - 1);
			line[1].position = sf::Vector2f(this->x + this->width, j - 1);

			if (yCur.first == 0) {
				line[0].color = sf::Color(0x202020FF);
				line[1].color = sf::Color(0x202020FF);
			}
			else {
				line[0].color = sf::Color(0xC0C0C0FF);
				line[1].color = sf::Color(0xC0C0C0FF);
			}
			window.draw(line);
		}
		yPrev = yCur;
		yCur = yNext;
	}
	return;
}

void GraphDrawer::drawNumbers(sf::RenderWindow& window) {
	double multiplier = 0.125;
	if (this->scale > 500) multiplier = 8;
	else if (this->scale > 250) multiplier = 4;
	else if (this->scale > 100) multiplier = 2;
	else if (this->scale > 50) multiplier = 1;
	else if (this->scale > 25) multiplier = 0.5;
	else if (this->scale > 15) multiplier = 0.25;

	double intpart;
	std::pair<double, double> xPrev, xCur, xNext;
	xPrev.second = std::modf(std::abs(this->pointToCoordinate(sf::Vector2f(this->x + 49, 0)).x) * multiplier, &intpart);
	xPrev.first = intpart;
	xCur.second = std::modf(std::abs(this->pointToCoordinate(sf::Vector2f(this->x + 50, 0)).x) * multiplier, &intpart);
	xCur.first = intpart;
	for (int16_t j = this->x + 51; j <= this->x + this->width - 50; ++j) {
		xNext.second = std::modf(std::abs(this->pointToCoordinate(sf::Vector2f(j, 0)).x) * multiplier, &intpart);
		xNext.first = intpart;

		if (xCur.second <= xPrev.second && xCur.second < xNext.second) {
			// Prepearing beautifuly looking number
			int32_t num = this->pointToCoordinate(sf::Vector2f(j - 1, 0)).x * 8; // For correct working .125 numbers
			int32_t a = std::abs(num / 8);
			uint16_t b = std::abs((num % 8) * 125);
			while (b % 10 == 0 && b > 0) b /= 10;

			sf::Text text;	
			text.setFont(this->font);
			text.setCharacterSize(TEXT_SIZE / 2);
			text.setFillColor(sf::Color(0x000000FF));
			if (num < 0) {
				text.setString("-" + std::to_string(a) + "." + std::to_string(b));
			}
			else {
				text.setString(std::to_string(a) + "." + std::to_string(b));
			}

			sf::FloatRect bounds = text.getLocalBounds();
			text.setOrigin(bounds.width / 2.0, bounds.height);
			text.setPosition(j - 1, this->y + this->height - 10);

			sf::RectangleShape bg;
			bg.setFillColor(sf::Color(0xFFFFFFA0));
			bg.setSize(sf::Vector2f(bounds.width + 2 * PADDING_SIZE, TEXT_SIZE / 3 + 2 * PADDING_SIZE));
			bg.setOrigin(bounds.width / 2 + PADDING_SIZE, TEXT_SIZE / 6 + PADDING_SIZE);
			bg.setPosition(sf::Vector2f(j - 1, this->y + this->height - 10));

			window.draw(bg);
			window.draw(text);
		}
		xPrev = xCur;
		xCur = xNext;
	}

	std::pair<double, double> yPrev, yCur, yNext;
	yPrev.second = std::modf(std::abs(this->pointToCoordinate(sf::Vector2f(0, this->y + 49)).y) * multiplier, &intpart);
	yPrev.first = intpart;
	yCur.second = std::modf(std::abs(this->pointToCoordinate(sf::Vector2f(0, this->y + 50)).y) * multiplier, &intpart);
	yCur.first = intpart;
	for (int16_t j = this->y + 51; j <= this->y + this->height - 50; ++j) {
		yNext.second = std::modf(std::abs(this->pointToCoordinate(sf::Vector2f(0, j)).y) * multiplier, &intpart);
		yNext.first = intpart;

		if (yCur.second <= yPrev.second && yCur.second < yNext.second) {
			// Prepearing beautifuly looking number
			int32_t num = this->pointToCoordinate(sf::Vector2f(0, j - 1)).y * 8; // For correct working .125 numbers
			int32_t a = std::abs(num / 8);
			uint16_t b = std::abs((num % 8) * 125);
			while (b % 10 == 0 && b > 0) b /= 10;

			sf::Text text;
			text.setFont(this->font);
			text.setCharacterSize(TEXT_SIZE / 2);
			text.setFillColor(sf::Color(0x000000FF));
			if (num < 0) {
				text.setString("-" + std::to_string(a) + "." + std::to_string(b));
			}
			else {
				text.setString(std::to_string(a) + "." + std::to_string(b));
			}

			sf::FloatRect bounds = text.getLocalBounds();
			text.setOrigin(0, TEXT_SIZE / 3);
			text.setPosition(this->x + 10, j - 1);

			sf::RectangleShape bg;
			bg.setFillColor(sf::Color(0xFFFFFFA0));
			bg.setSize(sf::Vector2f(bounds.width + 2 * PADDING_SIZE, TEXT_SIZE / 3 + 2 * PADDING_SIZE));
			bg.setOrigin(PADDING_SIZE, TEXT_SIZE / 6 + PADDING_SIZE);
			bg.setPosition(sf::Vector2f(this->x + 10, j - 1));

			window.draw(bg);
			window.draw(text);
		}
		yPrev = yCur;
		yCur = yNext;
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
	for (double i = this->x; i < this->x + this->width; i+=this->precisions[this->curPrecision]) {
		double graphX = this->pointToCoordinate(sf::Vector2f(i, 0)).x;
		double graphY = graph->calc(graphX);
		double j = this->coordinateToPoint(sf::Vector2f(0, graphY)).y;

		if (i > this->x) {
			if ((j > this->y && j < this->y + this->height && lastPoint.y > -32768 && lastPoint.y < 32767) ||
				(graphY > -32768 && graphY < 32767 && this->coordinateToPoint(lastPoint).y > this->y && this->coordinateToPoint(lastPoint).y < this->y + this->height)) {
				sf::VertexArray line(sf::LinesStrip, 2);
				line[0].position = this->coordinateToPoint(lastPoint);
				line[1].position = sf::Vector2f(i, j);
				line[0].color = sf::Color(graph->color);
				line[1].color = sf::Color(graph->color);

				window.draw(line);
			}
		}
		lastPoint = sf::Vector2f(graphX, graphY);
	}
	return;
}