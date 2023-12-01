//
// Created by gabri on 29/11/2023.
//

#include "GameData.h"

void GameData::save(const std::string &filename, Game& Game){
    game = Game;
    FILE* file = fopen(filename.c_str(), "w");
    if (file) {
        int numScores = scores.size();
        std::cout << numScores;
        fprintf(file, "%d\n", numScores);

        for (size_t i = 0; i < numScores; ++i) {
            int score = scores[i];
            fprintf(file, "%d\n" , score);
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

void GameData::load(const std::string &filename, Game& Game) {
    FILE* file = fopen(filename.c_str(), "rb");
    if (file) {
        int numScores;
        fscanf(file, "%d", &numScores);

        for (size_t i = 0; i < numScores; ++i) {
            int NewScore;
            fscanf(file, "%d", &NewScore);
        }

        Game.getPlayer()->deserialize(file);

        fscanf(file, "%d", &countEnemies);

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




