#pragma once

#include <iostream>
#include <fstream>
#include <functional>
#include "Round.h"
#include "Constants.h"

struct GameData
{
    // stats
    int population = 100;
    int balance = 2800;
    int territory = 1000;

    int round = 1;
    int resultMortality = 0;
    int desiredFood = 0;
    int desiredHarvest = 300;
    
    void saveData();
    void loadData();
};

char getValidatedChar(const std::string &text, std::function<bool (int)> validator);

// check for an existing save
void saveChecker(GameData& game);
bool askSave(GameData& game);
void yearResult(GameData& game, RoundData& round);
void gameResults(GameData& game);