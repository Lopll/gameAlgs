
#include <iostream>
#include <regex>
#include <string>
#include <random>
#include <cassert>

int dice(std::string rollConfig)
{
    using namespace std;
    int result = 0;
    
    // multi dice    
    size_t ind = rollConfig.find(',');
    if(ind != string::npos && rollConfig.find('d', ind) != string::npos)
    {
        result += dice(rollConfig.substr(ind+(size_t)1));
        if (result < 0) 
        {   
            return result;
        }
    }
    
    // parse
    regex dicePattern("(\\d+)d(\\d+)\\s*([+\\-])?\\s*(\\d+)?");// any number, d, any number, possible white-space, symbol +-, ws, num 
    smatch match;
    int diceCount;
    int rndMax;
    char postOperator;
    if(regex_search(rollConfig, match, dicePattern))
    {
        diceCount = stoi(match[1]);
        rndMax = stoi(match[2]);
        if (match[3].str() != "")
        {
            postOperator = match[3].str()[0];
            assert(match[4] != "");
        }
    }
    else
    {
        cerr << "ERROR: wrong dice format!";
        return -1;
    }
    
    // get random num with possible value changes
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> diceDist(1,rndMax);
    for(int i = 0; i < diceCount; i++)
    {
        result += diceDist(rng);
    }
    switch(postOperator)
    {
        case '+':
            result += stoi(match[4]);
            break;
        case '-':
            result -= stoi(match[4]);
            break;
    }
    // cout << "Result = " << result << endl;
    return result;
}

void check(std::string d, int maxRnd)
{   
    int n = 1000;

    int arr[maxRnd]{};
    for(int i = 0; i < n; i++)
    {
        int roll = dice(d);
        // std::cout<<roll<<std::endl;
        arr[(roll-1)%maxRnd]++;
    }
    
    std::cout << "Results of " << d << ": ";
    for(int i = 0; i < maxRnd; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout<<std::endl;
}

int main()
{   
    check("1d6", 6);
    check("2d6", 6);
    check("3d6", 6);
    check("1d10", 10);
    check("2d10", 10);
    check("3d10", 10);
    return 0;
}