#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

class BitcoinExchange
{
public:
    BitcoinExchange();
    BitcoinExchange(std::string input_file);
    BitcoinExchange(const BitcoinExchange &copy);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange();

    bool check_zero(std::string s);
    void read_and_save_data();
    void calculateBitcoinValue(const std::string &input_file);
    bool isValidDateFormat(const std::string &dateStr);
    void parseExchangeRateFile(const std::string &exchangeRateFile);
    double findClosestExchangeRate(const std::string &date) const;
    const std::map<std::string, double> &getExchangeRateMap() const;

    std::string &leftTrim(std::string &str, const std::string &chars);
    std::string &rightTrim(std::string &str, const std::string &chars);
    std::string &trimString(std::string &str, const std::string &chars);

    bool isLeapYear(int year);
    bool isValidDate(const std::string& dateStr);

private:
    std::string input_file;
    std::map<std::string, double> dataMap;
};

#endif