#include "../include/Round.h"

int deathProc(const int &population, const int &foodAmount)
{
    int alivePopulation = foodAmount/LIFE_PRICE;
    return (alivePopulation < population) ? population-alivePopulation : 0;
}

int cameProc(const int &mortarity, const int &harvest, const int &balance)
{
    int eqv = mortarity/2 + (5 - harvest) * balance/600 + 1;
    
    int result = eqv;
    if (result < 0) 
        result = 0;
    if (result > 50)
        result = 50;
         
    return result;
}
