#include "FormulaTree.h"

void FormulaTree::deleteTree() {
	this->deleteSubtree(this->start);
	return;
}

double FormulaTree::calc(const double& x) {
	return this->calcSubtree(this->start, x);
}

void FormulaTree::convertPolynom(std::string polynom) {
	this->deleteTree();
	if (polynom == "") return;

	polynom = polynom + ')';
	std::stack<std::string> operations;
	operations.push("(");
	std::stack<Node*> nodes;

	double number = 0;
	uint8_t signsAfterZero = 1;
	std::string last = "(";
	for (uint16_t i = 0; i < polynom.size(); ++i) {
		// A lot of different situations
		if (last == "(") {
			if (polynom[i] == ' ') {
				continue;
			}
			if (polynom[i] == '(') {
				operations.push("(");
				last = "(";
				continue;
			}
			if (polynom[i] == '0') {
				last = "leadingZero";
				continue;
			}
			if (polynom[i] >= '1' && polynom[i] <= '9') {
				last = "number";
				number = polynom[i] - '0';
				continue;
			}
			if (polynom[i] == '+') {
				last = "operation";
				continue;
			}
			if (polynom[i] == '-') {
				nodes.push(new Node(0));
				operations.push("-");
				last = "operation";
				continue;
			}
			if (polynom[i] == 'x' || polynom[i] == 't' || polynom[i] == 'e') {
				nodes.push(new Node(std::string(1, polynom[i])));
				last = "letter";
				continue;
			}
			if (polynom[i] == 'a' || polynom[i] == 's' || polynom[i] == 'c') {
				last = polynom[i];
				continue;
			}
		}
		if (last == "leadingZero") {
			if (polynom[i] == ' ') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				last = "numberSpace";
				continue;
			}
			if (polynom[i] == '(') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				operations.push("(");
				last = "(";
				continue;
			}
			if (polynom[i] == '.') {
				last = ".";
				continue;
			}
			if (polynom[i] == '+' || polynom[i] == '-') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == '*' || polynom[i] == '/') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos" && operations.top() != "+" && operations.top() != "-") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == '^') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos" && operations.top() != "+" && operations.top() != "-" && operations.top() != "*" && operations.top() != "/") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == 'x' || polynom[i] == 't' || polynom[i] == 'e') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos" && operations.top() != "+" && operations.top() != "-" && operations.top() != "*" && operations.top() != "/" && operations.top() != "^") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				nodes.push(new Node(std::string(1, polynom[i])));
				operations.push("*");
				last = "letter";
				continue;
			}
			if (polynom[i] == 'a' || polynom[i] == 's' || polynom[i] == 'c') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				operations.push("*");
				last = polynom[i];
				continue;
			}
			if (polynom[i] == ')') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				while (!operations.empty() && operations.top() != "(") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				if (!operations.empty()) {
					operations.pop();
					last = ")";
					continue;
				}
			}
		}
		if (last == "number") {
			if (polynom[i] == ' ') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				last = "numberSpace";
				continue;
			}
			if (polynom[i] == '(') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				operations.push("*");
				operations.push("(");
				last = "(";
				continue;
			}
			if (polynom[i] >= '0' && polynom[i] <= '9') {
				number = number * 10 + polynom[i] - '0';
				last = "number";
				continue;
			}
			if (polynom[i] == '.') {
				last = ".";
				continue;
			}
			if (polynom[i] == '+' || polynom[i] == '-') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == '*' || polynom[i] == '/') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos" && operations.top() != "+" && operations.top() != "-") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == '^') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos" && operations.top() != "+" && operations.top() != "-" && operations.top() != "*" && operations.top() != "/") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == 'x' || polynom[i] == 't' || polynom[i] == 'e') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos" && operations.top() != "+" && operations.top() != "-" && operations.top() != "*" && operations.top() != "/" && operations.top() != "^") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				nodes.push(new Node(std::string(1, polynom[i])));
				operations.push("*");
				last = "letter";
				continue;
			}
			if (polynom[i] == 'a' || polynom[i] == 's' || polynom[i] == 'c') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				operations.push("*");
				last = polynom[i];
				continue;
			}
			if (polynom[i] == ')') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				while (!operations.empty() && operations.top() != "(") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				if (!operations.empty()) {
					operations.pop();
					last = ")";
					continue;
				}
			}
		}
		if (last == "operation") {
			if (polynom[i] == ' ') {
				continue;
			}
			if (polynom[i] == '(') {
				operations.push("(");
				last = "(";
				continue;
			}
			if (polynom[i] == '0') {
				last = "leadingZero";
				continue;
			}
			if (polynom[i] >= '1' && polynom[i] <= '9') {
				number = polynom[i] - '0';
				last = "number";
				continue;
			}
			if (polynom[i] == 'x' || polynom[i] == 't' || polynom[i] == 'e') {
				nodes.push(new Node(std::string(1, polynom[i])));
				last = "letter";
				continue;
			}
			if (polynom[i] == 'a' || polynom[i] == 's' || polynom[i] == 'c') {
				last = polynom[i];
				continue;
			}
		}
		if (last == "letter") {
			if (polynom[i] == ' ') {
				last = "letterSpace";
				continue;
			}
			if (polynom[i] == '(') {
				operations.push("*");
				operations.push("(");
				last = "(";
				continue;
			}
			if (polynom[i] == '+' || polynom[i] == '-') {
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == '*' || polynom[i] == '/') {
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos" && operations.top() != "+" && operations.top() != "-") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == '^') {
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos" && operations.top() != "+" && operations.top() != "-" && operations.top() != "*" && operations.top() != "/") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == 'x' || polynom[i] == 't' || polynom[i] == 'e') {
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos" && operations.top() != "+" && operations.top() != "-" && operations.top() != "*" && operations.top() != "/" && operations.top() != "^") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				nodes.push(new Node(std::string(1, polynom[i])));
				operations.push("*");
				last = "letter";
				continue;
			}
			if (polynom[i] == 'a' || polynom[i] == 's' || polynom[i] == 'c') {
				operations.push("*");
				last = polynom[i];
				continue;
			}
			if (polynom[i] == ')') {
				while (!operations.empty() && operations.top() != "(") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				if (!operations.empty()) {
					operations.pop();
					last = ")";
					continue;
				}
			}
		}
		if (last == "a") {
			if (polynom[i] == 'b') {
				last = "ab";
				continue;
			}
		}
		if (last == "ab") {
			if (polynom[i] == 's') {
				last = "abs";
				continue;
			}
		}
		if (last == "abs") {
			if (polynom[i] == ' ') {
				continue;
			}
			if (polynom[i] == '(') {
				operations.push("(");
				operations.push("abs");
				last = "(";
				continue;
			}
		}
		if (last == "s") {
			if (polynom[i] == 'i') {
				last = "si";
				continue;
			}
			if (polynom[i] == 'q') {
				last = "sq";
				continue;
			}
		}
		if (last == "si") {
			if (polynom[i] == 'n') {
				last = "sin";
				continue;
			}
		}
		if (last == "sin") {
			if (polynom[i] == ' ') {
				continue;
			}
			if (polynom[i] == '(') {
				operations.push("(");
				operations.push("sin");
				last = "(";
				continue;
			}
		}
		if (last == "sq") {
			if (polynom[i] == 'r') {
				last = "sqr";
				continue;
			}
		}
		if (last == "sqr") {
			if (polynom[i] == 't') {
				last = "sqrt";
				continue;
			}
		}
		if (last == "sqrt") {
			if (polynom[i] == ' ') {
				continue;
			}
			if (polynom[i] == '(') {
				operations.push("(");
				operations.push("sqrt");
				last = "(";
				continue;
			}
		}
		if (last == "c") {
			if (polynom[i] == 'o') {
				last = "co";
				continue;
			}
		}
		if (last == "co") {
			if (polynom[i] == 's') {
				last = "cos";
				continue;
			}
		}
		if (last == "cos") {
			if (polynom[i] == ' ') {
				continue;
			}
			if (polynom[i] == '(') {
				operations.push("(");
				operations.push("cos");
				last = "(";
				continue;
			}
		}
		if (last == "numberSpace") {
			if (polynom[i] == ' ') {
				continue;
			}
			if (polynom[i] == '(') {
				operations.push("(");
				last = "(";
				continue;
			}
			if (polynom[i] == '+' || polynom[i] == '-') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == '*' || polynom[i] == '/') {
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos" && operations.top() != "+" && operations.top() != "-") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == '^') {
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos" && operations.top() != "+" && operations.top() != "-" && operations.top() != "*" && operations.top() != "/") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == ')') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				while (!operations.empty() && operations.top() != "(") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				if (!operations.empty()) {
					operations.pop();
					last = ")";
					continue;
				}
			}
		}
		if (last == ".") {
			if (polynom[i] >= '0' && polynom[i] <= '9') {
				number = number + (polynom[i] - '0') / std::pow(10, signsAfterZero);
				++signsAfterZero;
				last = "floatNumber";
				continue;
			}
		}
		if (last == "floatNumber") {
			if (polynom[i] == ' ') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				last = "numberSpace";
				continue;
			}
			if (polynom[i] == '(') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				operations.push("*");
				operations.push("(");
				last = "(";
				continue;
			}
			if (polynom[i] >= '0' && polynom[i] <= '9') {
				number = number + (polynom[i] - '0') / std::pow(10, signsAfterZero);
				++signsAfterZero;
				last = "floatNumber";
				continue;
			}
			if (polynom[i] == '+' || polynom[i] == '-') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == '*' || polynom[i] == '/') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos" && operations.top() != "+" && operations.top() != "-") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == '^') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos" && operations.top() != "+" && operations.top() != "-" && operations.top() != "*" && operations.top() != "/") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == 'x' || polynom[i] == 't' || polynom[i] == 'e') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos" && operations.top() != "+" && operations.top() != "-" && operations.top() != "*" && operations.top() != "/" && operations.top() != "^") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				nodes.push(new Node(std::string(1, polynom[i])));
				operations.push("*");
				last = "letter";
				continue;
			}
			if (polynom[i] == 'a' || polynom[i] == 's' || polynom[i] == 'c') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				operations.push("*");
				last = polynom[i];
				continue;
			}
			if (polynom[i] == ')') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				while (!operations.empty() && operations.top() != "(") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				if (!operations.empty()) {
					operations.pop();
					last = ")";
					continue;
				}
			}
		}
		if (last == "letterSpace") {
			if (polynom[i] == ' ') {
				continue;
			}
			if (polynom[i] == '+' || polynom[i] == '-') {
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == '*' || polynom[i] == '/') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos" && operations.top() != "+" && operations.top() != "-") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == '^') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos" && operations.top() != "+" && operations.top() != "-" && operations.top() != "*" && operations.top() != "/") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == ')') {
				nodes.push(new Node(number));
				number = 0;
				signsAfterZero = 1;
				while (!operations.empty() && operations.top() != "(") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				if (!operations.empty()) {
					operations.pop();
					last = ")";
					continue;
				}
			}
		}
		if (last == ")") {
			if (polynom[i] == ' ') {
				continue;
			}
			if (polynom[i] == '(') {
				nodes.push(new Node(std::string(1, polynom[i])));
				operations.push("*");
				operations.push("(");
				last = "(";
				continue;
			}
			if (polynom[i] == '+' || polynom[i] == '-') {
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == '*' || polynom[i] == '/') {
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos" && operations.top() != "+" && operations.top() != "-") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == '^') {
				while (operations.top() != "(" && operations.top() != "abs" && operations.top() != "sqrt" && operations.top() != "sin" && operations.top() != "cos" && operations.top() != "+" && operations.top() != "-" && operations.top() != "*" && operations.top() != "/") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				operations.push(std::string(1, polynom[i]));
				last = "operation";
				continue;
			}
			if (polynom[i] == 'a' || polynom[i] == 's' || polynom[i] == 'c') {
				operations.push("*");
				last = polynom[i];
				continue;
			}
			if (polynom[i] == ')') {
				while (!operations.empty() && operations.top() != "(") {
					Node* cur = new Node(operations.top()); operations.pop();
					if (cur->operation == "abs" || cur->operation == "sqrt" || cur->operation == "sin" || cur->operation == "cos") {
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
					}
					else {
						Node* right = nodes.top(); nodes.pop();
						Node* left = nodes.top(); nodes.pop();
						cur->left = left;
						cur->right = right;
					}
					nodes.push(cur);
				}
				if (!operations.empty()) {
					operations.pop();
					last = ")";
					continue;
				}
			}
		}

		if (i == polynom.size() - 1 && !operations.empty()) {
			throw Error("FormulaTree", "Unexpected end of expression");
		}
		else {
			throw Error("FormulaTree", "Unexpected \"" + std::string(1, polynom[i]) + "\" at position " + std::to_string(i + 1));
		}
	}

	if (!operations.empty()) {
		throw Error("FormulaTree", "Unexpected end of expression");
	}
	this->start = nodes.top();

	return;
}

void FormulaTree::deleteSubtree(Node*& node) {
	if (node == nullptr) return;

	this->deleteSubtree(node->left);
	this->deleteSubtree(node->right);
	delete node;
	node = nullptr;

	return;
}

double FormulaTree::calcSubtree(Node* node, const double& x) {
	if (start == nullptr) {
		throw Error("FormulaTree", "Cannot count empty tree");
	}

	// A lot of operations
	if (node->operation == "number") return node->number;
	if (node->operation == "x") return x;
	if (node->operation == "t") return clock() / double(CLOCKS_PER_SEC);
	if (node->operation == "e") return std::exp(1);
	if (node->operation == "+") return this->calcSubtree(node->left, x) + this->calcSubtree(node->right, x);
	if (node->operation == "-") return this->calcSubtree(node->left, x) - this->calcSubtree(node->right, x);
	if (node->operation == "*") return this->calcSubtree(node->left, x) * this->calcSubtree(node->right, x);
	if (node->operation == "/") return this->calcSubtree(node->left, x) / this->calcSubtree(node->right, x);
	if (node->operation == "^") return std::pow(this->calcSubtree(node->left, x), this->calcSubtree(node->right, x));
	if (node->operation == "abs") return std::abs(this->calcSubtree(node->left, x));
	if (node->operation == "sqrt") return std::sqrt(this->calcSubtree(node->left, x));
	if (node->operation == "sin") return std::sin(this->calcSubtree(node->left, x));
	if (node->operation == "cos") return std::cos(this->calcSubtree(node->left, x));

	throw Error("FormulaTree", "Unexpected operation - " + node->operation);
}