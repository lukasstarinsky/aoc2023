#include <sstream>
#include <algorithm>
#include "AOC.hpp"

#ifdef Day2
std::vector<std::string> SplitGameIntoCubes(const std::string& game){
    std::vector<std::string> output;
    std::stringstream gameStream(game);
    std::string setSplit;

    while (std::getline(gameStream, setSplit, ';'))
    {
        if (setSplit[0] == ' ')
            setSplit.erase(0, 1);

        std::stringstream setStream(setSplit);
        std::string cubeSplit;

        while (std::getline(setStream, cubeSplit, ','))
        {
            if (cubeSplit[0] == ' ')
                cubeSplit.erase(0, 1);

            output.push_back(cubeSplit);
        }
    }

    return output;
}

int Part1()
{
    std::ifstream inputFile("data/Day2.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open input data file.\n";
        return 0;
    }

    std::string line;
    int possibleGamesIdsSum = 0;

    while (std::getline(inputFile, line))
    {
        int gameId = std::stoi(line.substr(5, line.find(':') - 5));
        std::string game = line.substr(line.find(':') + 2, std::string_view::npos);

        bool isSetPossible = true;
        for (const auto& cube : SplitGameIntoCubes(game))
        {
            char colorChar[16];
            int count;

            sscanf_s(cube.c_str(), "%d %s", &count, colorChar);

            std::string color = colorChar;
            if (color == "red" && count > 12 || color == "green" && count > 13 || color == "blue" && count > 14)
                isSetPossible = false;
        }
        if (isSetPossible)
            possibleGamesIdsSum += gameId;
    }

    return possibleGamesIdsSum;
}

int Part2()
{
    std::ifstream inputFile("data/Day2.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open input data file.\n";
        return 0;
    }

    std::string line;
    int sumTotalPower = 0;

    while (std::getline(inputFile, line))
    {
        int fewestRed = 0, fewestGreen = 0, fewestBlue = 0;
        std::string game = line.substr(line.find(':') + 2, std::string_view::npos);

        for (const auto& cube : SplitGameIntoCubes(game))
        {
            char colorChar[16];
            int count;

            sscanf_s(cube.c_str(), "%d %s", &count, colorChar);

            std::string color = colorChar;

            if (color == "red" && count > fewestRed)
                fewestRed = count;
            else if (color == "green" && count > fewestGreen)
                fewestGreen = count;
            else if (color == "blue" && count > fewestBlue)
                fewestBlue = count;
        }
        sumTotalPower += fewestRed * fewestGreen * fewestBlue;
    }

    return sumTotalPower;
}

void AOC::Run()
{
    std::cout << "Part 1: " << Part1() << std::endl;
    std::cout << "Part 2: " << Part2() << std::endl;
}
#endif