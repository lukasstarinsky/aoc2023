#include "AOC.hpp"

#ifdef Day6
int Part1()
{
    std::ifstream inputFile("data/Day6.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open input data file.\n";
        return 0;
    }

    std::string times;
    std::string distances;
    std::getline(inputFile, times);
    std::getline(inputFile, distances);
    std::stringstream timesStream(times);
    std::stringstream distancesStream(distances);

    std::string _;
    timesStream >> _;
    distancesStream >> _;

    int time;
    int distance;
    int total = 1;
    while (timesStream >> time && distancesStream >> distance)
    {
        int numWaysToBeatRecord = 0;
        for (int i = 1; i < time; ++i)
        {
            if (i * (time - i) > distance)
                ++numWaysToBeatRecord;
        }
        total *= numWaysToBeatRecord;
    }

    return total;
}

int Part2()
{
    std::ifstream inputFile("data/Day6.txt");

    if (! inputFile.is_open())
    {
        std::cerr << "Failed to open input data file.\n";
        return 0;
    }

    std::string times;
    std::string distances;
    std::getline(inputFile, times);
    std::getline(inputFile, distances);
    std::stringstream timesStream(times);
    std::stringstream distancesStream(distances);

    std::string _;
    timesStream >> _;
    distancesStream >> _;

    std::string timePart;
    std::string distancePart;
    std::string timeString;
    std::string distanceString;

    while (timesStream >> timePart && distancesStream >> distancePart)
    {
        timeString += timePart;
        distanceString += distancePart;
    }
    u64 time = std::stoull(timeString);
    u64 distance = std::stoull(distanceString);

    int numWaysToBeatRecord = 0;
    for (u64 i = 1; i < time; ++i)
    {
        if (i * (time - i) > distance)
            ++numWaysToBeatRecord;
    }

    return numWaysToBeatRecord;
}

void AOC::Run()
{
    std::cout << "Part 1: " << Part1() << std::endl;
    std::cout << "Part 2: " << Part2() << std::endl;
}
#endif