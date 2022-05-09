#pragma once
#include <algorithm>
#include <cmath>
#include <stack>
#include <time.h>

#include "Containers.h"

class FormulaTree
{
public:
	void deleteTree();

	double calc(const double& x = 0);

	void convertPolynom(std::string polynom);

private:
	struct Node {
		double number = 0;
		std::string operation = "number";

		Node(const double& number) {
			this->number = number;
			return;
		}

		Node(const std::string& operation) {
			this->operation = operation;
			return;
		}

		Node* left = nullptr;
		Node* right = nullptr;
	};

	Node* start = nullptr;

	void deleteSubtree(Node*& node);

	double calcSubtree(Node* node, const double& x = 0);
};

