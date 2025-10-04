#include "../include/Input.h"

int getValidatedInt(const GameData& game, const std::string &text, std::function<bool (int)> validator)
{
    int result;
    
    while(true)
    {
        std::cout << text;
        if(std::cin >> result && validator(result))
        {
            return result;
        }
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "О, повелитель, пощади нас! У нас только " << game.population << " человек, " << game.balance << " бушелей пшеницы и " << game.territory << " акров земли" << std::endl;
    }
}

int transactionInput(const GameData& game, const int& price)
{
    std::string text;;
    int maxValue;
    if (price > 0)
    {
        text = "Сколько акров земли повелеваешь купить? ";
        maxValue = game.balance / price;
    }
    else
    {
        text = "Сколько акров земли повелеваешь продать? ";
        maxValue = game.territory;
    }
    return getValidatedInt(game, text, [maxValue](int v){ return v >= 0 && v <= maxValue;});
}

int foodInput(const GameData& game)
{
    return getValidatedInt(game, "Сколько бушелей пшеницы повелеваешь съесть? ", [game](int v){ return v >= 0 && v <= game.balance;});
}

int seedInput(const GameData& game)
{
    int availableTerritory = game.population * HUMAN_HARVESTING_POWER;

    int maxValue = std::min(std::min(availableTerritory, game.territory), (int) (game.balance/SEED_PRICE));
    return getValidatedInt(game, "Сколько акров земли повелеваешь засеять? ", [maxValue](int v){ return v >= 0 && v <= maxValue;});
}
