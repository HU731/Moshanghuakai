#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <ctime>
#include <algorithm>

struct Prize 
{
    int id;
    int pid;
    int type;
    std::string name;
    int total;
    int chance;
    int daynum;
    int pay;
};

class Lottery 
{
public:
    Lottery(){
        initPrizes();
    }
    Prize getPrize()
    {
        filterPrizesByUserPay();
        calculateChances();
        return drawPrize();
    }
private:
    std::vector<Prize> prizes;
    int userPay = 3000; 
    const int totalChance = 10000;
    void initPrizes(){
        prizes = 
        {
            {1, 11, 1, "典藏英雄", 20, 1000, 10, 2000},
            {2, 12, 1, "史诗皮肤", 40, 1000, 10, 4000},
            {3, 13, 1, "钻石奖励", 80, 1000, 10, 4000},
            {4, 14, 1, "荣耀水晶", 20, 1000, 10, 8000}
        };
    }
    void filterPrizesByUserPay(){
        prizes.erase(std::remove_if(prizes.begin(), prizes.end(), [this](const Prize& p) {
            return p.pay > userPay;
        }), prizes.end());
    }

    void calculateChances(){
        int nowChance = std::accumulate(prizes.begin(), prizes.end(), 0, [](int acc, const Prize& p) {
            return acc + p.chance;
        });
        int remainChance = totalChance - nowChance;
        prizes.push_back({0, 0, 1, "谢谢参与", 0, remainChance, 0, 0});
    }
    Prize drawPrize(){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, totalChance);

        int rand = distrib(gen);
        int currentChance = 0;

        for (auto& prize : prizes) 
        {
            currentChance += prize.chance;
            if (rand <= currentChance) 
            {
                return prize; 
            }
        }
        return {0, 0, 1, "Error", 0, 0, 0, 0}; 
    }
};

int main() 
{
    Lottery lottery;
    Prize prize = lottery.getPrize();
    std::cout << "赢了: "<< prize.name << std::endl;
    return 0;
}
