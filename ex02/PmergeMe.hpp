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
    void insert(std::deque<int> &nums, std::deque<int> b);
    void insertion_sort(std::deque<int>& nums);
    void johnson_sort_deque(std::deque<int>& nums);
    void fint_johnson_sort_deque();
    std::deque<int>::iterator customBinarySearchInsertion(std::deque<int>& sortedSequence, int elem);
    
    // vector
    void insert(std::vector<int> &nums, std::vector<int> b);
    void insertion_sort(std::vector<int> &nums);
    void johnson_sort_vector(std::vector<int> &nums);
    void fint_johnson_sort_vector();
    std::vector<int>::iterator customBinarySearchInsertion(std::vector<int>& sortedSequence, int elem);


    // getters
    std::vector<int> getVectorData() const;
    std::deque<int> getDequeData() const;

private:
    std::string expression;
    std::vector<int> vector_data;
    std::deque<int> deque_data;
    void fint_johnson_sort(std::vector<int> &data, size_t low, size_t high);
    void fint_johnson_sort(std::deque<int> &data, size_t low, size_t high);
};

#endif
