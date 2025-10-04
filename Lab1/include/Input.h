#pragma once

#include <iostream>
#include <functional>
#include <algorithm>
#include "Constants.h"
#include "Game.h"

int getValidatedInt(const GameData& game, const std::string &text, std::function<bool (int)> validator);
// returns user-defined acrs amount (with balance check)
int transactionInput(const GameData& game, const int& price);
// returns amount of consumed food
int foodInput(const GameData& game);
// returns user-defined amount of acrs for seeding
int seedInput(const GameData& game);