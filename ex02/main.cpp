#include <iostream>
#include <string>
#include "PmergeMe.hpp"
#include <iomanip>

std::string &leftTrim(std::string &str, const std::string &chars)
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

std::string &rightTrim(std::string &str, const std::string &chars)
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

std::string &trimString(std::string &str, const std::string &chars)
{
    return leftTrim(rightTrim(str, chars), chars);
}

template <typename Container>
void printContainerData(const std::string &containerType, const Container &data, double duration) {
    std::cout << "After: ";
    for (typename Container::const_iterator it = data.begin(); it != data.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Time to process a range of " << data.size() << " elements with " << containerType << ": "
              << std::fixed << std::setprecision(5) << duration * 1e6 << " us" << std::endl;
}


int main(int argc, char **argv) {
    (void)argc;
    if (argc > 1) {
        std::string chars_to_trim = "\n\t\v\f\r ";
        std::string result;
        argv++;
        while (*argv) {
            result += *argv;
            result += " ";
            argv++;
        }
        std::string expression = trimString(result, chars_to_trim);
        try {
            PmergeMe p(expression);
            std::vector<int> sorted_vector;
            std::deque<int> sorted_deque;

            // Measure time for vector
            clock_t start_time = clock();
            sorted_vector = p.ford_johnson_insertion_sort_vector();
            clock_t end_time = clock();
            double vector_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

            // Measure time for deque
            start_time = clock();
            sorted_deque = p.ford_johnson_insertion_sort_dequeue();
            end_time = clock();
            double deque_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

            std::cout << "Before: " << expression << std::endl;

            printContainerData("std::vector", sorted_vector, vector_time);
            printContainerData("std::deque", sorted_deque, deque_time);
        } catch (std::exception &e) {
            std::cerr << "Error" << std::endl;
        }
    }
    return 0;
}