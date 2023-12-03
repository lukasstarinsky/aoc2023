#include <map>
#include "AOC.hpp"

#ifdef Day3
typedef std::pair<int, int> Gear;
typedef std::vector<int> PartNumbers;

void FindAdjacentNumbers(const std::vector<std::string>& schematic, std::map<Gear, PartNumbers>& gearNumbers)
{
    for (const auto& [gearCoords, gearAdjacents]: gearNumbers)
    {
        const int gearX = gearCoords.first;
        const int gearY = gearCoords.second;

        for (int y = gearY - 1; y <= gearY + 1; ++y)
        {
            if (y < 0)
                continue;

            for (int x = 0; x < schematic[y].size(); ++x)
            {
                std::string num;
                for (int x2 = x; x2 < schematic[y].size(); ++x2)
                {
                    if (!isdigit(schematic[y][x2]))
                        break;

                    num += schematic[y][x2];
                    x = x2;
                }

                if (!num.empty())
                {
                    if (gearX >= x - (int)num.length() && gearX <= x + 1)
                        gearNumbers[gearCoords].push_back(std::stoi(num));
                }
            }
        }
    }
}

int Part1()
{
    std::ifstream inputFile("data/Day3.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open input data file.\n";
        return 0;
    }

    std::string line;
    std::vector<std::string> schematic;

    while (inputFile >> line)
    {
        schematic.push_back(line);
    }

    std::map<Gear, PartNumbers> gearNumbers;
    int sum = 0;

    for (int y = 0; y < schematic.size(); ++y)
    {
        for (int x = 0; x < schematic[y].size(); ++x)
        {
            if (!isdigit(schematic[y][x]) && schematic[y][x] != '.')
                gearNumbers.insert({{x, y}, {}});
        }
    }
    FindAdjacentNumbers(schematic, gearNumbers);

    for (const auto& [gearCoords, gearAdjacents]: gearNumbers)
    {
        for (const auto& gearNum: gearAdjacents)
        {
            sum += gearNum;
        }
    }

    return sum;
}

int Part2()
{
    std::ifstream inputFile("data/Day3.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open input data file.\n";
        return 0;
    }

    std::string line;
    std::vector<std::string> schematic;

    while (inputFile >> line)
    {
        schematic.push_back(line);
    }

    std::map<Gear, PartNumbers> gearNumbers;
    int gearRatioSum = 0;

    for (int y = 0; y < schematic.size(); ++y)
    {
        for (int x = 0; x < schematic[y].size(); ++x)
        {
            if (schematic[y][x] == '*')
                gearNumbers.insert({{x, y}, {}});
        }
    }
    FindAdjacentNumbers(schematic, gearNumbers);

    for (const auto& [gearCoords, gearAdjacents]: gearNumbers)
    {
        if (gearAdjacents.size() == 1 || gearAdjacents.empty())
            continue;

        int gearRatio = 1;
        for (const auto& gearNum: gearAdjacents)
        {
            gearRatio *= gearNum;
        }
        gearRatioSum += gearRatio;
    }

    return gearRatioSum;
}

void AOC::Run()
{
    std::cout << "Part 1: " << Part1() << std::endl;
    std::cout << "Part 2: " << Part2() << std::endl;
}
#endif