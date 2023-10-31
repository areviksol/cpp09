#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <vector>

class RPN {
public:
    RPN();
    RPN(const std::string& expression);
    RPN(const RPN &copy);
    RPN &operator=(const RPN &other);
    ~RPN();

    bool isOperator(const std::string& token);
    double performOperation(double operand1, double operand2, const std::string& op);
    double evaluate();
    bool check_zero(std::string s);
    bool valid(std::string token);
private:
    std::string expression;
    std::stack<double> operands;
};

#endif