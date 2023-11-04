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
void prdoubleContainerData(const std::string &containerType, const Container &data, double duration)
{
    std::cout << "After: ";
    for (typename Container::const_iterator it = data.begin(); it != data.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Time to process a range of " << data.size() << " elements with " << containerType << ": "
              << std::fixed << std::setprecision(5) << duration * 1e6 << " us" << std::endl;
}

int main(int argc, char **argv)
{
    if (argc >= 1)
    {
        std::string chars_to_trim = "\n\t\v\f\r ";
        std::string result;
        ++argv;
        while (*argv)
        {
            result += " ";
            result += *argv;
            ++argv;
        }

        std::string expression = trimString(result, chars_to_trim);

        try
        {
            PmergeMe p(expression);
            std::vector<double> sorted_vector;
            std::deque<double> sorted_deque;
            // Measure time for vector
            if(p.getVectorData().size() == 0) {
                std::cerr << "empty data" << std::endl;
                return 1;
            }
            clock_t start_time = clock();
            p.fint_johnson_sort_vector();
            clock_t end_time = clock();
            double vector_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

            start_time = clock();
            p.fint_johnson_sort_deque();
            end_time = clock();
            double deque_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

            std::cout << "Before: " << expression << std::endl;

            prdoubleContainerData("std::vector", p.getVectorData(), vector_time);
            prdoubleContainerData("std::deque", p.getDequeData(), deque_time);
        }
        catch (std::exception &e)
        {
            std::cerr << "Error" << std::endl;
        }
    }
    return 0;
}
