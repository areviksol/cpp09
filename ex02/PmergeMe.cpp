#include "PmergeMe.hpp"
#include <cmath>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const std::string &expression) : expression(expression)
{
    validation_and_save();
}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
    if (this != &copy)
        *this = copy;
    vector_data = copy.vector_data;
    deque_data = copy.deque_data;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this == &other)
    {
        return *this;
    }
    vector_data = other.vector_data;
    deque_data = other.deque_data;
    return *this;
}

PmergeMe::~PmergeMe() {}

bool PmergeMe::check_zero(std::string s)
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

void PmergeMe::validation_and_save()
{
    std::vector<std::string> tokens;

    std::istringstream iss(expression);

    std::string token;

    while (iss >> token)
    {
        int item = std::atof(token.c_str());
        if (check_zero(token) && errno != ERANGE)
        {
            deque_data.push_back(item);
            vector_data.push_back(item);
        }
        else
        {
            throw std::runtime_error("Error");
        }
    }
}

std::vector<int> PmergeMe::getVectorData() const
{
    return vector_data;
}
std::deque<int> PmergeMe::getDequeData() const
{
    return deque_data;
}

void PmergeMe::insert(std::deque<int> &nums, std::deque<int> b)
{
    int n = 0;
    int power = 0;
    size_t start_index = 0;
    size_t end_index = 0;

    for (size_t i = 0; i < b.size();)
    {
        ++power;

        n = pow(2, power) - n;

        start_index += n;

        end_index = start_index - n;

        if (start_index > b.size())
            start_index = b.size();

        for (size_t j = start_index - 1; j >= end_index;)
        {
            std::deque<int>::iterator it = std::upper_bound(nums.begin(), nums.end(), b[j]);
            nums.insert(it, b[j]);
            ++i;
            if (j == 0)
                break;
            --j;
        }
    }
}

void PmergeMe::insertion_sort(std::deque<int> &nums)
{
    for (size_t i = 1; i < nums.size(); ++i)
    {
        int j = i;
        while (j > 0 && nums[j] < nums[j - 1])
        {
            std::swap(nums[j], nums[j - 1]);
            j--;
        }
    }
}
std::deque<int>::iterator PmergeMe::customBinarySearchInsertion(std::deque<int>& sortedSequence, int elem) {
    return std::upper_bound(sortedSequence.begin(), sortedSequence.end(), elem);
}

void PmergeMe::johnson_sort_deque(std::deque<int> &nums) {
    int unpaired;
    std::deque<int> a, b;
    size_t size = nums.size() / 2 + (nums.size() % 2);

    unpaired = ((nums.size() % 2 == 0) ? -1 : nums[nums.size() - 1]);

    if (nums.size() == 2 || nums.size() == 3) {
        insertion_sort(nums);
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        if (i != size - 1 || nums.size() % 2 == 0) {
            int n = nums[i * 2], m = nums[i * 2 + 1];
            if (n > m)
                std::swap(n, m);
            a.push_back(m);
            b.push_back(n);
        }
    }

    if (unpaired != -1)
        b.push_back(unpaired);

    johnson_sort_deque(a);

    // Insert the remaining [n/2] - 1 elements of X \ S into S with binary search-based insertion
    std::deque<int> remainingElements;

    while (!b.empty()) {
        int elem = b.back();
        b.pop_back();
        std::deque<int>::iterator insertionPos = customBinarySearchInsertion(a, elem);
        a.insert(insertionPos, elem);
    }

    nums = a;
}


void PmergeMe::fint_johnson_sort_deque()
{
    if (deque_data.size() != 0 && deque_data.size() != 1)
    {
        johnson_sort_deque(deque_data);
    }
}

void PmergeMe::fint_johnson_sort_vector()
{
    if (vector_data.size() != 0 && vector_data.size() != 1)
    {
        johnson_sort_vector(vector_data);
    }
}

void PmergeMe::insert(std::vector<int> &nums, std::vector<int> b)
{
    int n = 0;
    int power = 0;
    size_t start_index = 0;
    size_t end_index = 0;

    for (size_t i = 0; i < b.size();)
    {
        ++power;

        n = static_cast<int>(std::pow(2, power)) - n;

        start_index += n;

        end_index = start_index - n;

        if (start_index > b.size())
            start_index = b.size();

        for (size_t j = start_index - 1; j >= end_index;)
        {
            std::vector<int>::iterator it = std::upper_bound(nums.begin(), nums.end(), b[j]);
            nums.insert(it, b[j]);
            ++i;
            if (j == 0)
                break;
            --j;
        }
    }
}

void PmergeMe::insertion_sort(std::vector<int> &nums)
{
    for (size_t i = 1; i < nums.size(); ++i)
    {
        int j = i;
        while (j > 0 && nums[j] < nums[j - 1])
        {
            std::swap(nums[j], nums[j - 1]);
            j--;
        }
    }
}

// Custom binary search function for insertion
std::vector<int>::iterator PmergeMe::customBinarySearchInsertion(std::vector<int>& sortedSequence, int elem) {
    return std::upper_bound(sortedSequence.begin(), sortedSequence.end(), elem);
}

void PmergeMe::johnson_sort_vector(std::vector<int> &nums) {
    int unpaired;
    std::vector<int> a, b;
    size_t size = nums.size() / 2 + (nums.size() % 2);

    unpaired = ((nums.size() % 2 == 0) ? -1 : nums[nums.size() - 1]);

    if (nums.size() == 2 || nums.size() == 3) {
        insertion_sort(nums);
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        if (i != size - 1 || nums.size() % 2 == 0) {
            int n = nums[i * 2], m = nums[i * 2 + 1];
            if (n > m)
                std::swap(n, m);
            a.push_back(m);
            b.push_back(n);
        }
    }

    if (unpaired != -1)
        b.push_back(unpaired);

    johnson_sort_vector(a);

    std::vector<int> remainingElements;

    while (!b.empty()) {
        int elem = b.back();
        b.pop_back();
        std::vector<int>::iterator insertionPos = customBinarySearchInsertion(a, elem);
        a.insert(insertionPos, elem);
    }

    nums = a;
}


