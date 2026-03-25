#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <map>

enum Mode { MODE_MATH, MODE_BINARY };

std::map<std::string, int> operatorPriority = {
    {"+", 1}, {"-", 1},
    {"*", 2}, {"/", 2},
    {"^", 3}, {"**", 3}, 

    {"&", 1}, {"|", 1}, {"==", 2} 
};

double Calculation_calcOp(double a, double b, std::string op, int currentMode) {
    if (currentMode == MODE_MATH) {
        if (op == "+") return a + b;
        else if (op == "-") return a - b;
        else if (op == "*") return a * b;
        else if (op == "/") {
            if (b == 0) throw std::runtime_error("Division by zero");
            return a / b;
        }
        else if (op == "^" || op == "**") return pow(a, b);
    } else if (currentMode == MODE_BINARY) {
        if (op == "&") return static_cast<int>(a) & static_cast<int>(b);
        else if (op == "|") return static_cast<int>(a) | static_cast<int>(b);
        else if (op == "==") return std::abs(a - b) < 1e-9;
    }

    throw std::runtime_error("Unknown operator: " + op);
}


double Calculation_evaluate(std::string expression, int currentMode = 0) {
    std::stack<double> values;
    std::stack<std::string> ops;

    for (int i = 0; i < expression.length(); i++) {
        if (isspace(expression[i])) continue;

        if (expression.substr(i, 3) == "log" && currentMode == MODE_MATH) {
            i += 3;
            while (i < expression.length() && isspace(expression[i])) i++;
            if (i >= expression.length() || expression[i] != '(') throw std::runtime_error("Expected '('");
            
            int count = 1; std::string content = ""; i++;
            while (i < expression.length() && count > 0) {
                if (expression[i] == '(') count++;
                if (expression[i] == ')') count--;
                if (count > 0) content += expression[i++];
            }
            size_t comma = content.find(',');
            if (comma == std::string::npos) throw std::runtime_error("Format: log(base,val)");
            
            double base = Calculation_evaluate(content.substr(0, comma));
            double x = Calculation_evaluate(content.substr(comma + 1));
            values.push(log(x) / log(base));
            continue;
        } else if (expression.substr(i, 3) == "log" && currentMode == MODE_BINARY) {
            throw std::runtime_error("log() is not allowed in Binary Mode");
        }

        if (isdigit(expression[i])) {
            std::string val = "";
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                val += expression[i++];
            }
            values.push(stod(val));
            i--;
        }
        else if (expression[i] == '(') {
            ops.push("(");
        }
        else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != "(") {
                std::string op = ops.top(); ops.pop();
                if (values.size() < 2) throw std::runtime_error("Invalid expression");
                double v2 = values.top(); values.pop();
                double v1 = values.top(); values.pop();
                values.push(Calculation_calcOp(v1, v2, op, currentMode));
            }
            if (ops.empty()) throw std::runtime_error("Mismatched parenthesis");
            ops.pop(); 
        }
        else {
            std::string op = "";
            op += expression[i];
            
            if (i + 1 < expression.length()) {
                std::string nextTwo = expression.substr(i, 2);
                if ((nextTwo == "==") || 
                    (nextTwo == "**")) {
                    op = nextTwo;
                    i++;
                }
            }

            int p = operatorPriority[op];
            if (p > 0) {
                bool isPower = (currentMode == MODE_MATH && (op == "^" || op == "**"));
                while (!ops.empty() && ops.top() != "(") {
                    int topP = operatorPriority[ops.top()];
                    if (topP > p || (topP == p && !isPower)) {
                        std::string topOp = ops.top(); ops.pop();
                        if (values.size() < 2) throw std::runtime_error("Invalid expression");
                        double v2 = values.top(); values.pop();
                        double v1 = values.top(); values.pop();
                        values.push(Calculation_calcOp(v1, v2, topOp, currentMode));
                    } else break;
                }
                ops.push(op);
            } else {
                throw std::runtime_error("Unknown operator: " + op);
            }
        }
    }

    while (!ops.empty()) {
        std::string op = ops.top(); ops.pop();
        if (op == "(") throw std::runtime_error("Mismatched parenthesis");
        if (values.size() < 2) throw std::runtime_error("Invalid expression");
        double v2 = values.top(); values.pop();
        double v1 = values.top(); values.pop();
        values.push(Calculation_calcOp(v1, v2, op, currentMode));
    }

    return values.top();
}

int main() {
    std::string choice;
    std::cout << "=== MODE SELECTION ===\n";
    std::cout << "1. Math Mode    (+, -, *, /, ^, **, log)\n";
    std::cout << "2. Binary Mode (&, |, ==)\n";
    std::cout << "Select: ";
    std::getline(std::cin, choice);

    Mode currentMode;

    if (choice == "1") {
        currentMode = MODE_MATH;
        std::cout << "[ MATH MODE ACTIVATED ]\n";
    } else if (choice == "2") {
        currentMode = MODE_BINARY;
        std::cout << "[ BINARY MODE ACTIVATED ]\n";
    } else {
        std::cerr << "Invalid choice, defaulting to Math Mode.\n";
        currentMode = MODE_MATH;
    }

    while (true) {
        std::string expr;
        std::cout << "\nEnter expression (or 'q' to quit):\n";
        std::cout << "> ";
        std::getline(std::cin, expr);
        
        if (expr == "q" || expr == "exit") break;
        if (expr.empty()) continue;

        try {
            std::cout << "= " << Calculation_evaluate(expr, currentMode) << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}