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
    double flag = 0;
    double flag2 = 0;
    for (std::string::iterator it = s.begin(), end = s.end(); it != end; ++it)
    {
        if (flag2 == 1 && *it == '.')
        {
            return false;
        }
        if (isdigit(*it) == 0)
        {
            if ((*it == 'E' || *it == 'e') && flag == 1)
            {
                if (!isdigit(*(it + 1)))
                {
                    return false;
                }
                continue;
            }
        }
        if (isdigit(*it) == 0)
        {
            if ((*it == 'F' || *it == 'f') && flag == 1)
            {
                if (*(it + 1))
                {
                    return false;
                }
                continue;
            }
        }
        if (isdigit(*it) == 0 && *it == '.')
        {
            flag2 = 1;
            if (isdigit(*(it + 1)) == 0)
            {
                return false;
            }
            continue;
        }
        if (isdigit(*it) == 0 && (*it != 'e' || *it != 'E' || *it != 'f' || *it != 'F' || *it != '.'))
        {
            return false;
        }
        flag = 1;
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
        double item = std::atof(token.c_str());
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

// double PmergeMe::binary_search(std::vector<double>& arr, size_t low, size_t high, double x)
// {
//     while (low <= high) {
//         size_t mid = (low + high) / 2;
//         if (arr[mid] == x) {
//             return mid;
//         } else if (arr[mid] > x) {
//             high = mid - 1;
//         } else {
//             low = mid + 1;
//         }
//     }
//     return low;
// }

// double PmergeMe::binary_search(std::deque<double>& arr, size_t low, size_t high, double x)
// {
//     while (low <= high) {
//         size_t mid = (low + high) / 2;
//         if (arr[mid] == x) {
//             return mid;
//         } else if (arr[mid] > x) {
//             high = mid - 1;
//         } else {
//             low = mid + 1;
//         }
//     }
//     return low;
// }

std::vector<double> PmergeMe::getVectorData() const
{
    return vector_data;
}
std::deque<double> PmergeMe::getDequeData() const
{
    return deque_data;
}
void PmergeMe::fint_johnson_sort(std::vector<double> &data, size_t low, size_t high)
{
    if (high - low <= 1)
    {
        return; // Base case, already sorted
    }

    size_t mid = (low + high) / 2;
    std::vector<double> left(data.begin() + low, data.begin() + mid);
    std::vector<double> right(data.begin() + mid, data.begin() + high);

    fint_johnson_sort(left, 0, left.size());
    fint_johnson_sort(right, 0, right.size());

    size_t i = 0, j = 0, k = low;

    while (i < left.size() && j < right.size())
    {
        if (left[i] < right[j])
        {
            data[k++] = left[i++];
        }
        else
        {
            data[k++] = right[j++];
        }
    }

    while (i < left.size())
    {
        data[k++] = left[i++];
    }

    while (j < right.size())
    {
        data[k++] = right[j++];
    }
}

void PmergeMe::fint_johnson_sort_vector()
{
    fint_johnson_sort(vector_data, 0, vector_data.size());
}

void PmergeMe::fint_johnson_sort_deque()
{
    fint_johnson_sort(deque_data, 0, deque_data.size());
}


void PmergeMe::fint_johnson_sort(std::deque<double> &data, size_t low, size_t high)
{
    if (high - low <= 1)
    {
        return; // Base case, already sorted
    }

    size_t mid = (low + high) / 2;
    std::deque<double> left(data.begin() + low, data.begin() + mid);
    std::deque<double> right(data.begin() + mid, data.begin() + high);

    fint_johnson_sort(left, 0, left.size());
    fint_johnson_sort(right, 0, right.size());

    size_t i = 0, j = 0, k = low;

    while (i < left.size() && j < right.size())
    {
        if (left[i] < right[j])
        {
            data[k++] = left[i++];
        }
        else
        {
            data[k++] = right[j++];
        }
    }

    while (i < left.size())
    {
        data[k++] = left[i++];
    }

    while (j < right.size())
    {
        data[k++] = right[j++];
    }
}

