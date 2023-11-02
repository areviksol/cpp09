#ifndef PMERGE_ME
#define PMERGE_ME

#include <vector>
#include <iostream>
#include <deque>
#include <sstream>
#include <ctype.h>
#include <cmath>

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

    // dequeue
    void insert(std::deque<double> &nums, std::deque<double> b);
    void insertion_sort(std::deque<double>& nums);
    void johnson_sort_deque(std::deque<double>& nums);
    void fint_johnson_sort_deque();

    // vector
    void insert(std::vector<double> &nums, std::vector<double> b);
    void insertion_sort(std::vector<double> &nums);
    void johnson_sort_vector(std::vector<double> &nums);
    void fint_johnson_sort_vector();

    // getters
    std::vector<double> getVectorData() const;
    std::deque<double> getDequeData() const;

private:
    std::string expression;
    std::vector<double> vector_data;
    std::deque<double> deque_data;
    void fint_johnson_sort(std::vector<double> &data, size_t low, size_t high);
    void fint_johnson_sort(std::deque<double> &data, size_t low, size_t high);
};

#endif
