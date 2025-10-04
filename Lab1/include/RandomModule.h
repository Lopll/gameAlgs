#include <random>

struct RandomModule
{
    std::mt19937 rng;
    std::uniform_int_distribution<int> harvestDist;
    std::uniform_int_distribution<int> plagueDist;
    std::uniform_int_distribution<int> ratDist;
    std::uniform_int_distribution<int> priceDist;
    
    RandomModule()
        :rng(std::random_device{}()),
         harvestDist(1,6),
         plagueDist(0,100),
         ratDist(0,7),
         priceDist(17, 26)
    {}
};