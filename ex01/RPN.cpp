#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const std::string &expression) : expression(expression) {}

RPN::RPN(const RPN &copy)
{
    if (this != &copy)
        *this = copy;
    expression = copy.expression;
    operands = copy.operands;
}

RPN &RPN::operator=(const RPN &other)
{
    if (this == &other)
    {
        return *this;
    }
    expression = other.expression;
    operands = other.operands;
    return *this;
}

RPN::~RPN() {

};

bool RPN:: isOperator(const std::string &token)
{
    return token == "+" || token == "-" || token == "*" || token == "/";
}

double RPN:: performOperation(double operand1, double operand2, const std::string &op)
{
    if (op == "+")
        return operand1 + operand2;
    else if (op == "-")
        return operand1 - operand2;
    else if (op == "*")
        return operand1 * operand2;
    else if (op == "/")
    {
        if (operand2 == 0)
        {
            std::cout << "Error: Division by zero" << std::endl;
            exit(1);
        }
        return operand1 / operand2;
    }else {
        throw std::runtime_error("Error: Invalid expression");    }
    return 0;
}


bool RPN::check_zero(std::string s)
{
    int flag = 0;
    for (std::string::iterator it = s.begin(), end = s.end(); it != end; ++it)
    {
        if (*it == '+' && flag == 0)
        {
            flag = 1;
            continue;
        }
        if (isdigit(*it) == 0)
        {
            return false;
        }
    }
    return true;
}

bool RPN::valid(std::string token)
{
    if (check_zero(token) && errno != ERANGE)
    {
        return true;
    }
    return false;
}

double RPN:: evaluate()
{
    std::istringstream iss(expression);
    std::stack<double> operands;
    std::string token;
    while (iss >> token)
    {
        if (!isOperator(token))
        {

            double num = std::atof(token.c_str());
            if(num < 0 || num >= 10){
                throw std::runtime_error("Error: Operands must be numbers at range 0-9");
            }
            if(!valid(token)){
                while (!operands.empty()) {
                    operands.pop();
                }                
                throw std::runtime_error("Error:");
            }
            operands.push(num);
        }
        else
        {
            if (operands.size() < 2)
            {
                std::cout << "Error: Insufficient operands for operation" << std::endl;
                exit(1);
            }
            double operand2 = operands.top();
            operands.pop();
            double operand1 = operands.top();
            operands.pop();
            try{
                double result = performOperation(operand1, operand2, token);
                operands.push(result);
            }catch(std::runtime_error &e){
                std::cout << e.what() << std::endl;
                exit(1);
            }
           
        }
    }

    if (operands.size() != 1)
    {
        std::cout << "Error: Invalid expression" << std::endl;
        exit(1);
    }

    return operands.top();
}