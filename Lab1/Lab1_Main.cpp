#include <iostream>
#include <fstream>
#include <windows.h>

#include "include/Input.h"
#include "include/Game.h"
#include "include/Round.h"
#include "include/Constants.h"
#include "include/RandomModule.h"

int main()
{
    using namespace std;
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    struct GameData game;
    struct RandomModule rm;
    struct RoundData round;
    
    saveChecker(game);

    for(; game.round <= GAME_LENGTH; game.round++)
    {
        // game logic
        cout << endl <<  "Мой повелитель, соизволь поведать тебе.\nВ году " << game.round << " твоего высочайшего правления..." << endl;
        
        round.price = rm.priceDist(rm.rng);
        
        if(game.round > 1)
        {
            round.mortality = deathProc(game.population, game.desiredFood);
            if (round.mortality/game.population >= 0.45)
            {
                cout << "Мой повелитель, вы нас уничтожили..." << endl;
                system("pause");
                return 0;
            }
            if (round.mortality > 0)
            {
                game.population -= round.mortality;
                game.resultMortality += round.mortality;
                game.balance -= game.population * LIFE_PRICE;
            }
            
            round.came = cameProc(round.mortality, round.harvest, game.balance);
            if(round.came > 0)
            {
                game.population += round.came;
            }
            
            round.plague = rm.plagueDist(rm.rng) <= PLAGUE_ODD;
            if (round.plague)
            {
                game.population /= 2;
            }
            
            round.ratFood = ((float) rm.ratDist(rm.rng)/100.0f) * game.balance;
            game.balance -= round.ratFood;
        }
        
        if (game.balance < 0)
        {
            game.balance = 0;
        }
        
        yearResult(game, round);
    
        // sell
        int transactionResult = transactionInput(game, -round.price); 
        game.territory -= transactionResult;
        game.balance += transactionResult * round.price;
        // buy
        transactionResult = transactionInput(game, round.price);
        game.territory += transactionResult;
        game.balance -= transactionResult * round.price;
        // feed
        game.desiredFood = foodInput(game);
        game.balance -= game.desiredFood;
        // seed
        round.harvest = rm.harvestDist(rm.rng);
        int seedInputResult = seedInput(game);
        game.desiredHarvest = seedInputResult * round.harvest;
        game.balance += game.desiredHarvest - (seedInputResult*SEED_PRICE);
        
        // continue?
        if (askSave(game))
        {
            system("pause");
            return 0;
        }
    }
    gameResults(game);
    
    system("pause");
    
    return 0;
}



