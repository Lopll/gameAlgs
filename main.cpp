#include <iostream>
#include <fstream>
#include <random>
#include <windows.h>

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
// returns value of potentinal transaction for user-defined acrs amount (with balance check)
int transactionInput(const int &price, const int &balance);
// returns amount of consumed food
int foodInput(const int &balance);
// returns needed wheat for harvesting user-defined amount of acrs
int harvestInput(const int &balance, const int &population, const int &harvest, const int &territory);

int main()
{
    using namespace std;
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
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
        cout << endl << "Мой повелитель, соизволь поведать тебе.\nВ году " << round << " твоего высочайшего правления..." << endl;
        harvest =  harvestDist(rng);
        price = priceDist(rng);
        
        if (mortality > 0)
        {
            cout << mortality << "человек умерли с голоду, ";
            population -= mortality;
            balance -= population * LIFE_PRICE;
        }
        if(came > 0)
        {
            cout << came << " человек прибыли в наш великий город;" << endl;
            population += came;
        }
        if (plague)
        {
            cout << "Чума уничтожила половину населения;" << endl;
            population /= 2;
        }
        else
        {
            cout << "Чума миновала наш великий город;" << endl;
        }
        cout << "Население города сейчас составляет " << population << " человек;" << endl;
        cout << "Мы собрали " << harvestResult << " бушелей пшеницы, ";
        cout << "по " << harvest << " бушелей с акра;" << endl;
        cout << "Крысы истребили " << ratFood << " бушелей пшеницы, оставив " << balance << " бушелей в амбарах;" << endl;
        cout << "Город сейчас занимает " << territory << " акров;" << endl;
        cout << "1 акр земли стоит сейчас " << price << " бушелей." << endl;
        cout << "Что пожелаешь, повелитель?" << endl;
        // inputs
        cout << "Сколько акров земли повелеваешь продать? ";
        balance += transactionInput(price, balance);
        
        cout << "Сколько акров земли повелеваешь купить? ";
        balance -= transactionInput(price, balance);
        
        food = foodInput(balance);
        balance -= food;
        
        harvestResult = harvestInput(balance, population, harvest, territory);
        balance += harvestResult;
        
        mortality = deathProc(population, food);
        came = cameProc(mortality, harvest, balance);
        plague = plagueDist(rng) <= PLAGUE_ODD;
        ratFood = ratDist(rng)/100 * balance;
        balance -= ratFood; 

        
    }
    
    int a;
    cin >> a; 
    
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

int transactionInput(const int &price, const int &balance)
{
    using namespace std;
    int desiredAcrs;
    while(true)
    {         
        if (!(cin >> desiredAcrs) || desiredAcrs < 0 || desiredAcrs * price > balance)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "О, повелитель, пощади нас! У нас только " << balance << " бушелей пшеницы" << endl;
            continue;
        }
        break;
    }
    return desiredAcrs * price;
}

int foodInput(const int &balance)
{
    using namespace std;
    int result;
    cout << "Сколько бушелей пшеницы повелеваешь съесть? " << endl;
    while(true)
    {         
        if (!(cin >> result) || result < 0 || result > balance)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "О, повелитель, пощади нас! У нас только " << balance << " бушелей пшеницы" << endl;
            continue;
        }
        break;
    }
    
    return result;
}

int harvestInput(const int &balance, const int &population, const int &harvest, const int &territory)
{
    using namespace std;
    int availableTerritory = population * HUMAN_HARVESTING_POWER;
    int desiredAcrs = 0;
    cout << "Сколько акров земли повелеваешь засеять? " << endl;
    while(true)
    {         
        if (!(cin >> desiredAcrs) || desiredAcrs < 0 || desiredAcrs > territory || 
            desiredAcrs > availableTerritory || desiredAcrs * harvest > balance)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "О, повелитель, пощади нас! У нас только " << population << " человек, " << balance << " бушелей пшеницы и " << territory << " акров земли!" << endl;
            continue;
        }
        break;
    }
    
    return desiredAcrs * harvest;
}