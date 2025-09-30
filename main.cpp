#include <iostream>
#include <fstream>
#include <random>

const int MAX_ROUND = 10;
const int LIFE_PRICE = 20;
const int MIN_HARVEST = 1;
const int MAX_HARVEST = 6;
const int PLAGUE_ODD = 15; // in %
const int HUMAN_HARVESTING_POWER = 10;

// returns amount of died people
int deathProc(const int &population, const int &foodAmount);
// returns amount of people, who came into the city
int cameProc(const int &mortarity, const int &harvest, const int &balance);
// return amount of harvested wheat
int harvestProc(const int &population, const int &harvest, const int &territory);

int main()
{
    using namespace std;
    
    //random config
    std::random_device rd;
    std:mt19937 rng(rd());
    
    std::uniform_int_distribution<int> harvestDist(MIN_HARVEST, MAX_HARVEST);
    std::uniform_int_distribution<int> plagueDist(0, 100);
    std::uniform_int_distribution<int> ratDist(0, 7);
    std::uniform_int_distribution<int> priceDist(17, 26);

    int round = 1;
    
    // stats
    int population = 1000;
    int balance = 2800;
    int territory = 1000;

    // player-decision amounts
    int bought = 0;
    int sell = 0;
    int food = 0;
    int seed = 0;
    
    // events notifiers
    int price;
    int harvest;
    int mortality = 0;
    int came = 0;
    bool plague = false;
    int harvestResult = 0;
    int ratFood = 0;
    
    for(; round <= 10; round++)
    {
        cout << endl << "Round " << round << endl;
        harvest =  harvestDist(rng);
        price = priceDist(rng);
        
        if (mortality > 0)
        {
            cout << "Deaths by starvation " << mortality << endl;
            population -= mortality;
            balance -= population * LIFE_PRICE;
        }
        
        if(came > 0)
        {
            cout << "People came " << came << endl;
            population += came;
        }
        
        if (plague)
        {
            cout << "PLAGUE!!!!" << endl;
            population /= 2;
        }
        else
        {
            cout << "NO PLAGUE" << endl;
        }
        
        cout << "Current population is " << population << endl;

        cout << "HARVEST RESULT is " << harvestResult << endl;
        cout << "HARVEST " << harvest << endl;
        
        cout << "Rat food is " << ratFood << endl;
        
        cout << "Territory is " << territory << endl;
        
        cout << "Price is " << price << endl;
        
        // TODO: buyInput(); с вводом-выводом и проверкой допустимости.
        
        mortality = deathProc(population, food);
        came = cameProc(mortality, harvest, balance);
        plague = plagueDist(rng) <= PLAGUE_ODD;
        harvestResult = harvestProc(population, harvest, territory);        
        balance += harvestResult;
        ratFood = ratDist(rng)/100 * balance;
        balance -= ratFood; 

        
    }
    
    return 0;
}

int deathProc(const int &population, const int &foodAmount)
{
    int alivePopulation = foodAmount/LIFE_PRICE;
    return (alivePopulation <= population) ? population-alivePopulation : 0;
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

int harvestProc(const int &population, const int &harvest, const int &territory)
{
    int availableTerritory = population * HUMAN_HARVESTING_POWER;
    int result = 0;
    if (availableTerritory < territory)
    {
        result = availableTerritory * harvest;
    }
    else
    {
        result = territory * harvest;
    }
    return result;
}