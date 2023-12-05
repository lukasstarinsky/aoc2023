#include <sstream>
#include "AOC.hpp"

#ifdef Day4
struct Card
{
    std::vector<int> WinningNumbers;
    std::vector<int> YourNumbers;
    int Count = 1;
};

std::vector<Card> LoadCards(std::ifstream& inputFile)
{
    std::string line;
    std::vector<Card> cards = {{}};

    while (std::getline(inputFile, line))
    {
        std::string _, cardNumber;
        std::stringstream lineStream(line);

        lineStream >> _ >> cardNumber;

        std::string buffer;
        bool isPart2 = false;
        Card card;
        while (lineStream >> buffer)
        {
            if (buffer == "|")
            {
                isPart2 = true;
                continue;
            }

            if (isPart2)
                card.YourNumbers.push_back(std::stoi(buffer));
            else
                card.WinningNumbers.push_back(std::stoi(buffer));
        }
        cards.push_back(card);
    }

    return cards;
}

int Part1()
{
    std::ifstream inputFile("data/Day4.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open input data file.\n";
        return 0;
    }

    std::vector<Card> cards = LoadCards(inputFile);
    int cardsWorthTotal = 0;
    for (const auto& card: cards)
    {
        bool isFirstMatch = true;
        int cardWorth = 0;
        for (const int winningNumber: card.WinningNumbers)
        {
            for (const int yourNumber: card.YourNumbers)
            {
                if (winningNumber == yourNumber)
                {
                    if (isFirstMatch)
                    {
                        cardWorth = 1;
                        isFirstMatch = false;
                    }
                    else
                        cardWorth *= 2;
                }
            }
        }
        cardsWorthTotal += cardWorth;
    }
    return cardsWorthTotal;
}

int Part2()
{
    std::ifstream inputFile("data/Day4.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open input data file.\n";
        return 0;
    }

    std::vector<Card> cards = LoadCards(inputFile);
    int totalCards = 0;
    for (int cardIndex = 1; cardIndex < cards.size(); ++cardIndex)
    {
        int matchingNumbers = 0;

        for (const int winningNumber: cards[cardIndex].WinningNumbers)
        {
            for (const int yourNumber: cards[cardIndex].YourNumbers)
            {
                if (winningNumber == yourNumber)
                    matchingNumbers++;
            }
        }

        for (int wonCardIndex = cardIndex + 1; wonCardIndex <= cardIndex + matchingNumbers; ++wonCardIndex)
        {
            cards[wonCardIndex].Count += cards[cardIndex].Count;
        }
        totalCards += cards[cardIndex].Count;
        cards[cardIndex].Count = 0;
    }

    return totalCards;
}

void AOC::Run()
{
    std::cout << "Part 1: " << Part1() << std::endl;
    std::cout << "Part 2: " << Part2() << std::endl;
}
#endif