#ifndef PMERGE_ME
#define PMERGE_ME

#include <vector>
#include <iostream>
#include <deque>
#include <sstream>
#include <ctype.h>

class PmergeMe
{
public:
    PmergeMe();
    PmergeMe(const std::string &expression);
    PmergeMe(const PmergeMe &copy);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();

    void validation_and_save();
    bool check_zero(std::string s);

    //dequeue
    std::deque<int> insertion_sort_dequeue(std::deque<int> data);
    std::deque<int> merge_dequeue(std::deque<int> left, std::deque<int> right);
    std::deque<int> ford_johnson_insertion_sort_dequeue();

    //vector
    std::vector<int> insertion_sort_vector(std::vector<int> data);
    std::vector<int> merge_vector(std::vector<int> left, std::vector<int> right);
    std::vector<int> ford_johnson_insertion_sort_vector();

    //getters
    std::vector<int> getVectorData() const;
    std::deque<int> getDequeData() const;
private:
    std::string expression;
    std::vector<int> vector_data;
    std::deque<int> deque_data;
};

#endif