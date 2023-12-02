#include <ranges>
#include <unordered_map>
#include "AOC.hpp"

#ifdef Day1
int Part1()
{
    std::ifstream inputFile("data/Day1.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open input data file.\n";
        return 0;
    }

    std::string line;
    int sum = 0;

    while (inputFile >> line)
    {
        std::string number;

        for (const char c : line)
        {
            if (std::isdigit(c))
            {
                number += c;
                break;
            }
        }
        for (const char c : std::ranges::reverse_view(line))
        {
           if (std::isdigit(c))
           {
               number += c;
               break;
           }
        }
        sum += std::stoi(number);
    }
    inputFile.close();

    return sum;
}

int Part2()
{
    std::ifstream inputFile("data/Day1.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open input data file.\n";
        return 0;
    }

    std::string line;
    int sum = 0;

    std::unordered_map<std::string, char> digitMap =
    {
        {"one", '1'},
        {"two", '2'},
        {"three", '3'},
        {"four", '4'},
        {"five", '5'},
        {"six", '6'},
        {"seven", '7'},
        {"eight", '8'},
        {"nine", '9'}
    };

    while (inputFile >> line)
    {
        std::string number;

        bool done = false;
        for (std::size_t i = 0; i < line.length(); ++i)
        {
            if (done)
                break;

            for (std::size_t j = 0; j <= i; ++j)
            {
                if (digitMap.contains(line.substr(j, i - j)))
                {
                    number += digitMap[line.substr(j, i - j)];
                    done = true;
                    break;
                }
            }

            if (!done && isdigit(line[i]))
            {
                number += line[i];
                done = true;
            }
        }

        done = false;
        for (std::size_t i = line.length() - 1; i >= 0; --i)
        {
            if (done)
                break;

            for (std::size_t j = i; j < line.length(); ++j)
            {
                if (digitMap.contains(line.substr(i, line.length() - j)))
                {
                    number += digitMap[line.substr(i, line.length() - j)];
                    done = true;
                    break;
                }
            }

            if (!done && std::isdigit(line[i]))
            {
                number += line[i];
                done = true;
            }
        }
        sum += std::stoi(number);
    }
    inputFile.close();

    return sum;
}

void AOC::Run()
{
    std::cout << "Part 1: " << Part1() << std::endl;
    std::cout << "Part 2: " << Part2() << std::endl;
}
#endif