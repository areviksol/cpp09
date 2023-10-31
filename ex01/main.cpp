#include "RPN.hpp"

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " \"RPN_expression\"" << std::endl;
        return 1;
    }

    std::string expression = argv[1];
    RPN rpn(expression);
    int result = rpn.evaluate();
    std::cout << result << std::endl;
    return 0;
}
