//
// Created by gabri on 29/11/2023.
//

#ifndef EXAME_CES11_GAMEDATA_H
#define EXAME_CES11_GAMEDATA_H

#include "../States/LevelState.h"

#include "../Headers/Game.h"

class GameData {
public:
    GameData(Game& game);

    void save(const std::string& filename, Game& Game, LevelState&, int&);
    void load(const std:: string& filename, Game& Game, LevelState&, int&);

    void saveTime(const std::string &filename, sf::Time &);
    std::vector<float> loadTime(const std::string &filename);
    float getLastTime(std::vector<float>);

    void rankingTimes(std::vector<float>&);
    std::vector<float> existentTimes;
private:
    LevelState map;

    Game game;
    int countBullets = 0;
    int countEnemies = 0;

};


#endif //EXAME_CES11_GAMEDATA_H
