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

        int numScores = scores.size();
        fprintf(file, "%d\n", numScores);

        for (size_t i = 0; i < numScores; ++i) {
            int score = scores[i];
            fprintf(file, "%d\n", score);
        }

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
            Map.level1.isPlayerOnMe = false;
        else Map.level1.isPlayerOnMe = true;

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

        int numScores;
        fscanf(file, "%d", &numScores);

        for (size_t i = 0; i < numScores; ++i) {
            int NewScore;
            fscanf(file, "%d", &NewScore);
            scores.push_back(NewScore);
        }

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

void GameData::addScore(int score) {
    scores.push_back(score);
}

void GameData::printScores() {
    ranking(scores);
    if (scores.empty()) {
        std::cout << "Nenhum score disponivel.\n";
        return;
    }
    std::cout << "------------" << std::endl;
    for(int i = 0; i < scores.size(); i++) {
        if(i < 6)
            std::cout << i + 1 << ": " << scores[i] << std::endl;
    }
    std::cout << "------------" << std::endl;
}

void GameData::ranking(std::vector<int>& scores) {
    int aux;

    for (int i=0; i < scores.size(); ++i){
        for (int j=i; j < scores.size(); ++j){
            if (scores[i] < scores[j]){
                aux = scores[i];
                scores[i] = scores[j];
                scores[j] = aux;
            }
        }
    }
}

GameData::GameData(Game& Game) {
    game = Game;
}




