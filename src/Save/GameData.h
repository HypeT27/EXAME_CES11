//
// Created by gabri on 29/11/2023.
//

#ifndef EXAME_CES11_GAMEDATA_H
#define EXAME_CES11_GAMEDATA_H
#include "../Entities/playerAttack.h"
#include "../Entities/Enemy.h"
#include "../Headers/Game.h"

class GameData {
public:
    GameData(Game& game);

    void save(const std::string& filename, Game& Game);
    void addScore(int score);
    void load(const std:: string& filename, Game& Game);
    void ranking(std::vector<int>& scores);

    void printScores();
private:
    Game game;
    int countBullets = 0;
    int countEnemies = 0;
    int countAttacks = 0;
    std::vector<int> scores;

};


#endif //EXAME_CES11_GAMEDATA_H
