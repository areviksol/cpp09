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

std::vector<double> PmergeMe::getVectorData() const
{
    return vector_data;
}
std::deque<double> PmergeMe::getDequeData() const
{
    return deque_data;
}

void PmergeMe::insert(std::deque<double> &nums, std::deque<double> b)
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
    std::deque<double>::iterator it = std::upper_bound(nums.begin(), nums.end(), b[j]);
    nums.insert(it, b[j]);
    ++i;
    if (j == 0)
        break;
    --j;
        }
    }
}

void PmergeMe::insertion_sort(std::deque<double> &nums)
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

void PmergeMe::johnson_sort_deque(std::deque<double> &nums)
{
    double unpaired;
    std::deque<double> a, b;
    size_t size = nums.size() / 2 + (nums.size() % 2);

    unpaired = ((nums.size() % 2 == 0) ? -1 : nums[nums.size() - 1]);

    if (nums.size() == 2 || nums.size() == 3)
    {
        insertion_sort(nums);
        return;
    }

    for (size_t i = 0; i < size; ++i)
    {
        if (i != size - 1 || nums.size() % 2 == 0)
        {
    double n = nums[i * 2], m = nums[i * 2 + 1];
    if (n > m)
        std::swap(n, m);
    a.push_back(m);
    b.push_back(n);
        }
    }

    if (unpaired != -1)
        b.push_back(unpaired);

    johnson_sort_deque(a);
    johnson_sort_deque(b);

    insert(a, b);
    nums = a;
}

void PmergeMe::fint_johnson_sort_deque()
{
    johnson_sort_deque(deque_data);
}

void PmergeMe::fint_johnson_sort_vector()
{
    johnson_sort_vector(vector_data);
}

    void PmergeMe::insert(std::vector<double> &nums, std::vector<double> b)
    {
        int n = 0;
        int power = 0;
        size_t start_index = 0;
        size_t end_index = 0;

        for (size_t i = 0; i < b.size();) {
            ++power;

            n = static_cast<int>(std::pow(2, power)) - n;

            start_index += n;

            end_index = start_index - n;

            if (start_index > b.size())
                start_index = b.size();

            for (size_t j = start_index - 1; j >= end_index;) {
                std::vector<double>::iterator it = std::upper_bound(nums.begin(), nums.end(), b[j]);
                nums.insert(it, b[j]);
                ++i;
                if (j == 0)
                    break;
                --j;
            }
        }
    }

    void PmergeMe::insertion_sort(std::vector<double> &nums)
    {
        for (size_t i = 1; i < nums.size(); ++i) {
            int j = i;
            while (j > 0 && nums[j] < nums[j - 1]) {
                std::swap(nums[j], nums[j - 1]);
                j--;
            }
        }
    }

    void PmergeMe::johnson_sort_vector(std::vector<double> &nums)
    {
        double unpaired;
        std::vector<double> a, b;
        size_t size = nums.size() / 2 + (nums.size() % 2);

        unpaired = ((nums.size() % 2 == 0) ? -1 : nums[nums.size() - 1]);

        if (nums.size() == 2 || nums.size() == 3) {
            insertion_sort(nums);
            return;
        }

        for (size_t i = 0; i < size; ++i) {
            if (i != size - 1 || nums.size() % 2 == 0) {
                double n = nums[i * 2], m = nums[i * 2 + 1];
                if (n > m)
                    std::swap(n, m);
                a.push_back(m);
                b.push_back(n);
            }
        }

        if (unpaired != -1)
            b.push_back(unpaired);

        johnson_sort_vector(a);
        johnson_sort_vector(b);

        insert(a, b);
        nums = a;
    }

