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

int main(int argc, char **argv)
{
    (void)argc;
    if(argc > 1) 
    {
        
        std::string chars_to_trim = "\n\t\v\f\r ";
        std::string result;
        argv++;
        while (*argv)
        {
            result += *argv;
            result += " ";
            argv++;
        }
        std::string expression = trimString(result, chars_to_trim);
        try
        {
            PmergeMe p(expression);
            std::vector<int> sorted_vector;
            std::deque<int> sorted_deque;

            // Measure time for vector
            std::chrono::high_resolution_clock::time_point start_vector = std::chrono::high_resolution_clock::now();
            sorted_vector = p.ford_johnson_insertion_sort_vector();
            std::chrono::high_resolution_clock::time_point end_vector = std::chrono::high_resolution_clock::now();

            // Measure time for deque
            std::chrono::high_resolution_clock::time_point start_deque = std::chrono::high_resolution_clock::now();
            sorted_deque = p.ford_johnson_insertion_sort_dequeue();
            std::chrono::high_resolution_clock::time_point end_deque = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> duration_vector = end_vector - start_vector;
            std::chrono::duration<double> duration_deque = end_deque - start_deque;

            std::cout << "Before: " << expression << std::endl;

            std::cout << "After: ";
            for (std::vector<int>::iterator it = sorted_vector.begin(); it != sorted_vector.end(); ++it)
            {
                std::cout << *it << " ";
            }
            std::cout << std::endl;

            std::cout << "Time to process a range of " << p.getVectorData().size() << " elements with std::vector: "
                    << std::fixed << std::setprecision(5) << duration_vector.count() * 1e6 << " us" << std::endl;

            std::cout << "After: ";
            for (std::deque<int>::iterator it = sorted_deque.begin(); it != sorted_deque.end(); ++it)
            {
                std::cout << *it << " ";
            }
            std::cout << std::endl;

            std::cout << "Time to process a range of elements with std::deque: "
                    << std::fixed << std::setprecision(5) << duration_deque.count() * 1e6 << " us" << std::endl;
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}