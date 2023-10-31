#include <iostream>
#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " input_file" << std::endl;
        return 1;
    }

    std::string input_file = argv[1];

    BitcoinExchange exchange(input_file);

    // std::map<std::string, double>::const_iterator it = exchange.getExchangeRateMap().begin();

    // while (it != exchange.getExchangeRateMap().end())
    // {
    //     std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
    //     ++it;
    // }

    exchange.calculateBitcoinValue(input_file);

    return 0;
}
