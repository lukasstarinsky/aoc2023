#include <sstream>
#include <limits>
#include <chrono>
#include "AOC.hpp"

#ifdef Day5
struct ConvertRange
{
    unsigned long DestinationStart;
    unsigned long SourceStart;
    unsigned long Length;
};

struct Almanac
{
    std::vector<unsigned long> Seeds;
    std::vector<std::vector<ConvertRange>> Maps = {{}, {}, {}, {}, {}, {}, {}};
};

Almanac LoadAlmanac(std::ifstream& inputFile, bool part2)
{
    Almanac almanac;
    std::string line;
    int loadingStage = -1;

    while (std::getline(inputFile, line))
    {
        if (line.empty())
        {
            loadingStage++;
            continue;
        }
        std::stringstream lineStream(line);

        if (loadingStage == -1)
        {
            std::string _;
            lineStream >> _;
            if (part2)
            {
                unsigned long rangeStart;
                unsigned long rangeLength;
                while (lineStream >> rangeStart >> rangeLength)
                {
                    for (unsigned long i = rangeStart; i < rangeStart + rangeLength; ++i)
                    {
                        almanac.Seeds.push_back(i);
                    }
                }
            }
            else
            {
                unsigned long num;
                while (lineStream >> num)
                    almanac.Seeds.push_back(num);
            }
            continue;
        }

        if (line.contains("map:"))
            continue;

        ConvertRange range = {};
        lineStream >> range.DestinationStart >> range.SourceStart >> range.Length;
        almanac.Maps[loadingStage].emplace_back(range);
    }

    return almanac;
}

void HandleConversion(std::vector<unsigned long>& convertedSeeds, const Almanac& almanac)
{
    for (const auto& map: almanac.Maps)
    {
        bool* isConverted = new bool[convertedSeeds.size()];
        std::fill(isConverted, isConverted + convertedSeeds.size(), false);

        for (const auto& convertRange: map)
        {
            for (int seedIndex = 0; seedIndex < convertedSeeds.size(); ++seedIndex)
            {
                if (!isConverted[seedIndex] && convertedSeeds[seedIndex] >= convertRange.SourceStart &&
                    convertedSeeds[seedIndex] <= convertRange.SourceStart + convertRange.Length - 1)
                {
                    convertedSeeds[seedIndex] = convertRange.DestinationStart + convertedSeeds[seedIndex] - convertRange.SourceStart;
                    isConverted[seedIndex] = true;
                }
            }
        }
        delete[] isConverted;
    }
}

unsigned long Part1()
{
    std::ifstream inputFile("data/Day5.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open input data file.\n";
        return 0;
    }

    Almanac almanac = LoadAlmanac(inputFile, false);
    std::vector<unsigned long> convertedSeeds = almanac.Seeds;
    HandleConversion(convertedSeeds, almanac);

    unsigned long lowestLocation = std::numeric_limits<int>::max();
    for (const unsigned long seed: convertedSeeds)
    {
        if (seed < lowestLocation)
            lowestLocation = seed;
    }

    return lowestLocation;
}

unsigned long Part2()
{
    std::ifstream inputFile("data/Day5.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open input data file.\n";
        return 0;
    }

    Almanac almanac = LoadAlmanac(inputFile, true);
    std::vector<unsigned long> convertedSeeds = almanac.Seeds;
    HandleConversion(convertedSeeds, almanac);

    unsigned long lowestLocation = std::numeric_limits<int>::max();
    for (const unsigned long seed: convertedSeeds)
    {
        if (seed < lowestLocation)
            lowestLocation = seed;
    }

    return lowestLocation;
}

void AOC::Run()
{
    using namespace std::chrono_literals;

    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Part 1: " << Part1() << std::endl;
    std::cout << "Part 2: " << Part2() << std::endl;
    auto end = std::chrono::high_resolution_clock::now();

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(end - start);
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Execution took: " << minutes << " <> " << seconds << " <> " << milliseconds << " \n";
}
#endif