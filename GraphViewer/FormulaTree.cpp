#include "FormulaTree.h"

void FormulaTree::deleteTree() {
	this->deleteSubtree(this->start);
	return;
}

double FormulaTree::count(const double& x) {
	return this->countSubtree(this->start, x);
}

void FormulaTree::convertPolynom(std::string polynom) {
	this->deleteTree();

	polynom = '(' + polynom + ')';

	std::stack<std::string> operations;
	std::stack<Node*> nodes;

	for (uint16_t i = 0; i < polynom.size(); ++i) {
	}

	return;
}

void FormulaTree::deleteSubtree(Node* node) {
	if (node == nullptr) return;

	this->deleteSubtree(node->left);
	this->deleteSubtree(node->right);
	delete node;

	return;
}

double FormulaTree::countSubtree(Node* node, const double& x) {
	if (start == nullptr) {
		throw Error("FormulaTree", "Cannot count empty tree");
	}

	// A lot of operations
	if (node->operation == "number") return node->number;
	if (node->operation == "x") return x;
	if (node->operation == "t") return clock() / double(CLOCKS_PER_SEC);
	if (node->operation == "+") return this->countSubtree(node->left, x) + this->countSubtree(node->right, x);
	if (node->operation == "-") return this->countSubtree(node->left, x) - this->countSubtree(node->right, x);
	if (node->operation == "*") return this->countSubtree(node->left, x) * this->countSubtree(node->right, x);
	if (node->operation == "/") return this->countSubtree(node->left, x) / this->countSubtree(node->right, x);
	if (node->operation == "pow") return std::pow(this->countSubtree(node->left, x), this->countSubtree(node->right, x));
	if (node->operation == "sin") return std::sin(this->countSubtree(node->left, x));
	if (node->operation == "cos") return std::cos(this->countSubtree(node->left, x));

	throw Error("FormulaTree", "Unexpected operation - " + node->operation);
}