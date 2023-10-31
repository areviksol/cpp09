#include "PmergeMe.hpp"

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
    int flag2 = 0;
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
// dequeue
std::deque<int> PmergeMe::insertion_sort_dequeue(std::deque<int> data)
{
    for (std::deque<int>::size_type i = 1; i < data.size(); i++)
    {
        int key = data[i];
        int j = i - 1;

        while (j >= 0 && data[j] > key)
        {
            data[j + 1] = data[j];
            j--;
        }

        data[j + 1] = key;
    }

    return data;
}

std::deque<int> PmergeMe::merge_dequeue(std::deque<int> left, std::deque<int> right)
{
    std::deque<int> result;

    std::deque<int>::iterator i = left.begin();
    std::deque<int>::iterator j = right.begin();

    while (i != left.end() && j != right.end())
    {
        if (*i < *j)
        {
            result.push_back(*i);
            i++;
        }
        else
        {
            result.push_back(*j);
            j++;
        }
    }

    while (i != left.end())
    {
        result.push_back(*i);
        i++;
    }

    while (j != right.end())
    {
        result.push_back(*j);
        j++;
    }

    return result;
}
std::deque<int> PmergeMe::ford_johnson_insertion_sort_dequeue()
{
    int n = deque_data.size();

    std::deque<int> result;
    for (int i = 0; i < n; i++)
    {
        std::deque<int> subarray;
        subarray.push_back(deque_data[i]);

        for (int j = i + 1; j < n; j++)
        {
            if (deque_data[j] < deque_data[i])
            {
                subarray.push_back(deque_data[j]);
                i = j;
            }
            else
            {
                break;
            }
        }

        subarray = insertion_sort_dequeue(subarray);
        result = merge_dequeue(result, subarray);
    }

    return result;
}

// vector
std::vector<int> PmergeMe::insertion_sort_vector(std::vector<int> data)
{
    for (std::vector<int>::size_type i = 1; i < data.size(); i++)
    {
        int key = data[i];
        int j = i - 1;

        while (j >= 0 && data[j] > key)
        {
            data[j + 1] = data[j];
            j--;
        }

        data[j + 1] = key;
    }

    return data;
}

std::vector<int> PmergeMe::merge_vector(std::vector<int> left, std::vector<int> right)
{
    std::vector<int> result;

    std::vector<int>::iterator i = left.begin();
    std::vector<int>::iterator j = right.begin();

    while (i != left.end() && j != right.end())
    {
        if (*i < *j)
        {
            result.push_back(*i);
            i++;
        }
        else
        {
            result.push_back(*j);
            j++;
        }
    }

    while (i != left.end())
    {
        result.push_back(*i);
        i++;
    }

    while (j != right.end())
    {
        result.push_back(*j);
        j++;
    }

    return result;
}

std::vector<int> PmergeMe::ford_johnson_insertion_sort_vector()
{
    int n = vector_data.size();

    std::vector<int> result;
    for (int i = 0; i < n; i++)
    {
        std::vector<int> subarray;
        subarray.push_back(vector_data[i]);

        for (int j = i + 1; j < n; j++)
        {
            if (vector_data[j] < vector_data[i])
            {
                subarray.push_back(vector_data[j]);
                i = j;
            }
            else
            {
                break;
            }
        }

        subarray = insertion_sort_vector(subarray);
        result = merge_vector(result, subarray);
    }

    return result;
}

std::vector<int> PmergeMe::getVectorData() const
{
    return vector_data;
}
std::deque<int> PmergeMe::getDequeData() const
{
    return deque_data;
}