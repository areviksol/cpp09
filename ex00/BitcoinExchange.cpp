#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(std::string input_file) : input_file(input_file)
{
    read_and_save_data();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
    if (this != &copy)
        *this = copy;
    input_file = copy.input_file;
    dataMap = copy.dataMap;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this == &other)
    {
        return *this;
    }
    input_file = other.input_file;
    dataMap = other.dataMap;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::read_and_save_data()
{
    std::ifstream file("data.csv");

    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }
    parseExchangeRateFile("data.csv");
}

bool BitcoinExchange::isValidDateFormat(const std::string &dateStr)
{
    if (dateStr.length() != 10)
    {
        return false;
    }

    if (dateStr[4] != '-' || dateStr[7] != '-')
    {
        return false;
    }

    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
        {
            if (dateStr[i] != '-')
                return false;
        }
        else
        {
            if (!isdigit(dateStr[i]))
                return false;
        }
    }

    return true;
}

bool BitcoinExchange::isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool BitcoinExchange::isValidDate(const std::string &dateStr)
{
    int year = 0, month = 0, day = 0;

    char delimiter;

    // Use a stringstream to parse the date string
    std::istringstream ss(dateStr);

    ss >> year >> delimiter >> month >> delimiter >> day;

    if (ss.eof() && ss.fail() == false && ss.bad() == false && delimiter == '-')
    {
        if (year >= 0 && month >= 1 && month <= 12 && day >= 1)
        {
            int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

            if (month == 2)
            {
                if (isLeapYear(year))
                {
                    return day <= 29;
                }
                else
                {
                    return day <= 28;
                }
            }
            else
            {
                return day <= daysInMonth[month];
            }
        }
    }

    return false;
}

bool BitcoinExchange::check_zero(std::string s)
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

void BitcoinExchange::parseExchangeRateFile(const std::string &exchangeRateFile)
{
    std::ifstream file(exchangeRateFile);
    std::string line;
    while (std::getline(file, line))
    {
        size_t found = line.find(",");
        if (found == std::string::npos)
        {
            continue;
        }
        std::string date = line.substr(0, found);
        std::string rateStr = line.substr(found + 1);
        double rate = std::atof(rateStr.c_str());
        if (check_zero(rateStr) || errno != ERANGE)
        {
            dataMap[date] = rate;
        }
    }
}

const std::map<std::string, double> &BitcoinExchange::getExchangeRateMap() const
{
    return this->dataMap;
}

std::string &BitcoinExchange::leftTrim(std::string &str, const std::string &chars)
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

std::string &BitcoinExchange::rightTrim(std::string &str, const std::string &chars)
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

std::string &BitcoinExchange::trimString(std::string &str, const std::string &chars)
{
    return leftTrim(rightTrim(str, chars), chars);
}

void BitcoinExchange::calculateBitcoinValue(const std::string &input_file)
{
    std::string chars_to_trim = "\t\v\f\r ";
    std::ifstream file(input_file);

    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    int flag = 0;
    while (std::getline(file, line))
    {
        size_t found = line.find("|");
        if (trimString(line, chars_to_trim).empty())
        {
            continue;
        }
        if (found == std::string::npos)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        std::string date = line.substr(0, found);
        std::string valueStr = line.substr(found + 1);
        if (trimString(date, chars_to_trim) == "date" && trimString(valueStr, chars_to_trim) == "value" && flag == 0)
        {
            flag = 1;
            continue;
        }else if (flag == 0)
        {
            std::cerr << "Wtong file " << std::endl;
            exit(1);
        }

        if (!isValidDateFormat(trimString(date, chars_to_trim)) || !isValidDate(trimString(date, chars_to_trim)))
        {
            std::cerr << "Error: invalid date format => " << date << std::endl;
            continue;
        }
        try
        {
            if(trimString(valueStr, chars_to_trim).empty()) {
                std::cerr << "Value must be a valid number " << std::endl;
                continue;
            }
            double value = std::atof(valueStr.c_str());
            if (!(check_zero(trimString(valueStr, chars_to_trim)) && errno != ERANGE))
            {
                std::cerr << "Value must be a valid number " << std::endl;
                continue;
            }

            if (value < 0.0 || value > 1000.0)
            {
                std::cerr << "Error: value must be between 0 and 1000." << std::endl;
                continue;
            }

            double exchangeRate = findClosestExchangeRate(date);
            if (exchangeRate != -1.0)
            {
                double bitcoinValue = value * exchangeRate;
                std::cout << date << " => " << value << " = " << bitcoinValue << std::endl;
            }
            else
            {
                std::cerr << "Error: closest exchange rate not found for date " << date << std::endl;
            }
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error: not a valid number." << std::endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cerr << "Error: too large a number." << std::endl;
        }
    }
}

double BitcoinExchange::findClosestExchangeRate(const std::string &date) const
{
    std::map<std::string, double>::const_iterator lower = dataMap.lower_bound(date);
    if (lower == dataMap.begin())
    {
        return lower->second;
    }
    if (lower == dataMap.end())
    {
        return std::prev(lower)->second;
    }
    std::map<std::string, double>::const_iterator prev = std::prev(lower);
    if (date.compare(lower->first) == 0)
    {
        return lower->second;
    }
    else
    {
        return prev->second;
    }
}
