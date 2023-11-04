#include "RPN.hpp"

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " \"RPN_expression\"" << std::endl;
        return 1;
    }
    try{
        std::string expression = argv[1];
        RPN rpn(expression);
        double result = rpn.evaluate();
        std::cout << result << std::endl;
    }catch (std::exception &e){
         std::cout << e.what() << std::endl;
    }
    return 0;
}
