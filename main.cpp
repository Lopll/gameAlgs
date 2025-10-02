#include <iostream>
#include <fstream>
#include <random>
#include <windows.h>
#include <fstream>

const int MAX_ROUND = 10;
const int LIFE_PRICE = 20;
const int MIN_HARVEST = 1;
const int MAX_HARVEST = 6;
const int PLAGUE_ODD = 15; // in %
const int HUMAN_HARVESTING_POWER = 10;
const int GAME_LENGTH = 10; // in rounds
const float SEED_PRICE = 0.5;

// returns amount of died people
int deathProc(const int &population, const int &foodAmount);
// returns amount of people, who came into the city
int cameProc(const int &mortarity, const int &harvest, const int &balance);
// return amount of harvested wheat
int harvestProc(const int &population, const int &harvest, const int &territory);
// returns user-defined acrs amount (with balance check)
int transactionInput(const int &price, const int &balance, const int &territory);
// returns amount of consumed food
int foodInput(const int &balance);
// returns user-defined amount of acrs for seeding
int seedInput(const int &balance, const int &population, const int &territory);

struct gameData
{
    // stats
    int population = 100;
    int balance = 2800;
    int territory = 1000;

    int round = 1;
    int resultMortality = 0;
    int desiredFood = 0;
    int desiredHarvest = 300;
    
    void saveData()
    {
        std::ofstream file("saves.txt");
        file.write(reinterpret_cast<char*>(this), sizeof(gameData));
        file.close();
    }
    
    void loadData()
    {
        std::ifstream file("saves.txt");
        if(!file)
            return;
        file.read(reinterpret_cast<char*>(this), sizeof(gameData));
        file.close();
    }
};

int main()
{
    using namespace std;
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    //random config
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> harvestDist(MIN_HARVEST, MAX_HARVEST);
    std::uniform_int_distribution<int> plagueDist(0, 100);
    std::uniform_int_distribution<int> ratDist(0, 7);
    std::uniform_int_distribution<int> priceDist(17, 26);
    
    struct gameData game;
    
    ifstream saveFile("saves.txt");
    if(saveFile)
    {
        cout << "Желаете загрузить сохранённую игру? (y/n)" << endl;
        char a;
        cin >> a;
        if (a == 'y')
        {
            game.loadData();
        }
    }
    
    for(; game.round <= GAME_LENGTH; game.round++)
    {
        // game logic
        cout << endl <<  "Мой повелитель, соизволь поведать тебе.\nВ году " << game.round << " твоего высочайшего правления..." << endl;
        
        int harvest = harvestDist(rng);
        int price = priceDist(rng);
        
        int mortality = 0;
        int came = 5;
        bool plague = false;
        int ratFood = 200;
        
        if(game.round > 1)
        {
            // continue?
            cout << endl << "Мой повелитель, помни, что ты волен отдохнуть. Для этого скажи только \"q\"" << endl;
            char q;
            cin >> q;
            if (q == 'q')
            {
                game.saveData();
                system("pause");
                return 0;
            }
        
            mortality = deathProc(game.population, game.desiredFood);
            came = cameProc(mortality, harvest, game.balance);
            plague = plagueDist(rng) <= PLAGUE_ODD;
            
            ratFood = ((float) ratDist(rng)/100.0f) * game.balance;
            game.balance -= ratFood;
        }
        
        if (mortality/game.population >= 0.45)
        {
            cout << "Мой повелитель, вы нас уничтожили..." << endl;
            system("pause");
            return 0;
        }
        if (mortality > 0)
        {
            cout << mortality << " человек умерли с голоду, и ";
            game.population -= mortality;
            game.resultMortality += mortality;
            game.balance -= game.population * LIFE_PRICE;
        }
        
        if(came > 0)
        {
            cout << came << " человек прибыли в наш великий город;" << endl;
            game.population += came;
        }
        
        if (plague)
        {
            cout << "Чума уничтожила половину населения;" << endl;
            game.population /= 2;
        }
        else
        {
            cout << "Чума миновала наш великий город;" << endl;
        }
        
        cout << "Население города сейчас составляет " << game.population << " человек;" << endl;
        
        cout << "Мы собрали " << game.desiredHarvest << " бушелей пшеницы, ";
        cout << "по " << harvest << " бушелей с акра;" << endl;
        
        cout << "Крысы истребили " << ratFood << " бушелей пшеницы, оставив " << game.balance << " бушелей в амбарах;" << endl;
        
        
        
        cout << "Город сейчас занимает " << game.territory << " акров;" << endl;
        cout << "1 акр земли стоит сейчас " << price << " бушелей." << endl;
        cout << "Что пожелаешь, повелитель?" << endl;


        // sell
        int transactionResult = transactionInput(-price, game.balance, game.territory); 
        game.territory -= transactionResult;
        game.balance += transactionResult * price;
        // buy
        transactionResult = transactionInput(price, game.balance, game.territory);
        game.territory += transactionResult;
        game.balance -= transactionResult * price;
        
        game.desiredFood = foodInput(game.balance);
        game.balance -= game.desiredFood;
        
        game.desiredHarvest = seedInput(game.balance, game.population, game.territory) * harvest;
        game.balance += game.desiredHarvest;
        
        if (game.balance < 0)
        {
            game.balance = 0;
        }
    }
    int mortalityGrade = game.resultMortality/GAME_LENGTH;
    int territoryGrade = game.territory/game.population;
    
    if (mortalityGrade > 33 && territoryGrade < 7)
    {
        cout << "Из-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас их города. Теперь вы вынуждены влачить жалкое существование в изгнании" << endl;
    }
    else if (mortalityGrade > 10 && territoryGrade < 9)
    {
        cout << "Вы правили железной рукой, подобно Нерону и Ивану Грозному. Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем" << endl;
    }
    else if (mortalityGrade > 3 && territoryGrade < 10)
    {
        cout << "Вы справились вполне неплохо, у вас, конечно, есть недоброжелатели, но многие хотели бы увидеть вас во главе города снова" << endl;
    }
    else
    {
        cout << "«Фантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше" << endl;
    }
    
    system("pause");
    
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

int transactionInput(const int &price, const int &balance, const int &territory)
{
    using namespace std;
    int desiredAcrs;
    
    if (price > 0)
    {
        cout << "Сколько акров земли повелеваешь купить? ";
    }
    else
    {
        cout << "Сколько акров земли повелеваешь продать? ";
    }
    
    while(true)
    {   
        if (!(cin >> desiredAcrs) || desiredAcrs < 0 || desiredAcrs * price > balance
            || (price < 0 && desiredAcrs > territory))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "О, повелитель, пощади нас! У нас только " << balance << " бушелей пшеницы и " << territory << "акров земли" << endl;
            continue;
        }
        break;
    }
    return desiredAcrs;
}

int foodInput(const int &balance)
{
    using namespace std;
    int result;
    cout << "Сколько бушелей пшеницы повелеваешь съесть? ";
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

int seedInput(const int &balance, const int &population, const int &territory)
{
    using namespace std;
    int availableTerritory = population * HUMAN_HARVESTING_POWER;
    int desiredAcrs = 0;
    cout << "Сколько акров земли повелеваешь засеять? ";
    while(true)
    {         
        if (!(cin >> desiredAcrs) || desiredAcrs < 0 || desiredAcrs > territory || 
            desiredAcrs > availableTerritory || desiredAcrs * SEED_PRICE > balance)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "О, повелитель, пощади нас! У нас только " << population << " человек, " << balance << " бушелей пшеницы и " << territory << " акров земли" << endl;
            continue;
        }
        break;
    }
    
    return desiredAcrs;
}