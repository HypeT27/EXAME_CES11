//
// Created by gabri on 29/11/2023.
//

#include "GameData.h"


void GameData::save(const std::string &filename, Game& Game, LevelState& Map, int& levelsCompleted){
    map = Map;
    game = Game;
    FILE* file = fopen(filename.c_str(), "w");
    if (file) {
        fprintf(file, "%d\n", game.getLevel());

        fprintf(file, "%d\n", levelsCompleted);

        fprintf(file, "%d\n", map.level1.isPlayerOnMe);
        fprintf(file, "%d\n", map.level2.isPlayerOnMe);
        fprintf(file, "%d\n", map.level3.isPlayerOnMe);
        fprintf(file, "%d\n", map.level4.isPlayerOnMe);

        fprintf(file, "%d\n", map.level1.isVisited);
        fprintf(file, "%d\n", map.level2.isVisited);
        fprintf(file, "%d\n", map.level3.isVisited);
        fprintf(file, "%d\n", map.level4.isVisited);

        game.getPlayer()->serialize(file);

        countEnemies = game.getEnemies().size();

        fprintf(file, "%d\n", countEnemies);

        for(auto i : game.getEnemies())
            i->serialize(file);

        countBullets = game.getBullets().size();
        fprintf(file, "%d\n", countBullets);

        for(auto i : game.getBullets()) {
            i->serialize(file);
        }

        fclose(file);
    }
}


void GameData::load(const std::string &filename, Game& Game, LevelState& Map, int& levelsCompleted) {
    FILE* file = fopen(filename.c_str(), "rb");
    if (file) {
        int newLevel;
        fscanf(file, "%d", &newLevel);

        fscanf(file, "%d", &levelsCompleted);

        int playerOn1;
        fscanf(file, "%d", &playerOn1);
        if(playerOn1 == 0)
            Map.level1.isPlayerOnMe = false;
        else Map.level1.isPlayerOnMe = true;

        int playerOn2;
        fscanf(file, "%d", &playerOn2);
        if(playerOn2 == 0)
            Map.level2.isPlayerOnMe = false;
        else Map.level2.isPlayerOnMe = true;

        int playerOn3;
        fscanf(file, "%d", &playerOn3);
        if(playerOn3 == 0)
            Map.level3.isPlayerOnMe = false;
        else Map.level3.isPlayerOnMe = true;

        int playerOn4;
        fscanf(file, "%d", &playerOn4);
        if(playerOn4 == 0)
            Map.level4.isPlayerOnMe = false;
        else Map.level4.isPlayerOnMe = true;

        int visited1;
        fscanf(file, "%d", &visited1);
        if(visited1 == 0)
            Map.level1.isVisited = false;
        else Map.level1.isVisited = true;

        int visited2;
        fscanf(file, "%d", &visited2);
        if(visited2 == 0)
            Map.level2.isVisited = false;
        else Map.level2.isVisited = true;

        int visited3;
        fscanf(file, "%d", &visited3);
        if(visited3 == 0)
            Map.level3.isVisited = false;
        else Map.level3.isVisited = true;

        int visited4;
        fscanf(file, "%d", &visited4);
        if(visited4 == 0)
            Map.level4.isVisited = false;
        else Map.level4.isVisited = true;


        Game.getPlayer()->deserialize(file);

        fscanf(file, "%d", &countEnemies);

        Game.changeEnemyCounter(countEnemies);
        Game.changeLevel(newLevel);


        for(int i = 0; i < countEnemies; i++) {
            Game.getEnemies()[i]->deserialize(file);
        }

        fscanf(file, "%d", &countBullets);
        for(int i = 0; i < countBullets; i++) {
            Game.addBullet();
            Game.getBullets()[i]->deserialize(file);
        }
        fclose(file);
    }
}

GameData::GameData(Game& Game) {
    game = Game;
}

void GameData::saveTime(const std::string &filename, sf::Time &timePassed) {
    existentTimes = loadTime(filename);
    existentTimes.push_back(timePassed.asSeconds());

    if(existentTimes.size() > 6)
        existentTimes.resize(6);\

    FILE* file = fopen(filename.c_str(), "w");
    if(file)
        for(float time: existentTimes)
            fprintf(file, "%f\n", time);

    fclose(file);
}

std::vector<float> GameData::loadTime(const std::string &filename) {
    std::vector<float> times;
    FILE* file = fopen(filename.c_str(), "r");

    if (file) {
        float time;
        while (fscanf(file, "%f\n", &time) != EOF) {
            times.push_back(time);
        }
        fclose(file);
    }
    return times;
}

void GameData::rankingTimes(std::vector<float> &existentTimes) {
    float aux;

    for (int i=0; i < existentTimes.size(); ++i){
        for (int j=i; j < existentTimes.size(); ++j){
            if (existentTimes[i] > existentTimes[j]){
                aux = existentTimes[i];
                existentTimes[i] = existentTimes[j];
                existentTimes[j] = aux;
            }
        }
    }

}

float GameData::getLastTime(std::vector<float> existentTimes) {
    if(!existentTimes.empty())
        return existentTimes.back();
}