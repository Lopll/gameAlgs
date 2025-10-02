#include "../include/Game.h"

char getValidatedChar(const std::string &text, std::function<bool (int)> validator)
{
    char result;
    
    while(true)
    {
        std::cout << text;
        if(std::cin >> result && validator(std::tolower(result)))
        {
            return std::tolower(result);
        }
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Что-что?" << std::endl;
    }
}

void GameData::saveData()
{
    std::ofstream file("saves.txt");
    file.write(reinterpret_cast<char*>(this), sizeof(GameData));
    file.close();
}

void GameData::loadData()
{
    std::ifstream file("saves.txt");
    if(!file)
    {
        return;
    }
    file.read(reinterpret_cast<char*>(this), sizeof(GameData));
    file.close();
}

void saveChecker(GameData& game)
{
    std::ifstream saveFile("saves.txt");
    if(saveFile)
    {
        if (getValidatedChar("Желаете загрузить сохранённую игру? (y/n)", [](int v){ return v == 'y' or v == 'n';}) == 'y')
        {
            game.loadData();
        }
    }
}

bool askSave(GameData& game)
{
    if (getValidatedChar("Мой повелитель, желаете продолжить правление? (y/n)", [](int v){ return v == 'y' or v == 'n';}) == 'n')
    {
        game.saveData();
        return true;
    }
    return false;
}

void yearReport(GameData& game, RoundData& round)
{
    using namespace std;
    
    if (round.mortality > 0)
    {
        cout << round.mortality << " человек умерли с голоду, и ";
        game.population -= round.mortality;
        game.resultMortality += round.mortality;
        game.balance -= game.population * LIFE_PRICE;
    }
    
    if(round.came > 0)
    {
        cout << round.came << " человек прибыли в наш великий город;" << endl;
        game.population += round.came;
    }
    
    if (round.plague)
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
    cout << "по " << round.harvest << " бушелей с акра;" << endl;
    
    cout << "Крысы истребили " << round.ratFood << " бушелей пшеницы, оставив " << game.balance << " бушелей в амбарах;" << endl;
    
    cout << "Город сейчас занимает " << game.territory << " акров;" << endl;
    cout << "1 акр земли стоит сейчас " << round.price << " бушелей." << endl;
    cout << "Что пожелаешь, повелитель?" << endl;
}

void gameResults(GameData& game)
{
    using namespace std;
    
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
}