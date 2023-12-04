//
// Created by gabri on 29/11/2023.
//

#include "../Headers/ScreenHandler.h"


ScreenHandler::ScreenHandler(): game(),gameData(game){
    renderState = MENUSCREEN;
    gameData = GameData(game);
}

void ScreenHandler::update(sf::RenderWindow& window) {
    switch (this->renderState) {
        case GAMESCREEN:
            game.updateDt();
            game.update(window);

            if(game.getEnemiesCounter() == 0){
                this->renderState = LEVELSCREEN;
                saveGame();
                break;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                this->renderState = MENUSCREEN;
                saveGame();
                break;
            }
            break;
        case MENUSCREEN:
            menu.update(window);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                this->renderState = LEVELSCREEN;
                newGame();
                break;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
                this->renderState = GAMESCREEN;
                loadGame();
                break;
            }

        case LEVELSCREEN:
            level.update(window);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
                if(!level.level1.isVisited) {
                    level.level1.isPlayerOnMe = true;
                    game.changeLevel(1);
                    level.level1.isVisited = true;
                    this->renderState = GAMESCREEN;
                    levelsCompleted++;
                    break;
                }
                else std::cout << "Already make this level";
                break;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
                if(actualLevel().points(&level.level2)) {
                    actualLevel().isPlayerOnMe = false;
                    if (!level.level2.isVisited) {
                        level.level2.isPlayerOnMe = true;
                        game.changeLevel(2);
                        level.level2.isVisited = true;
                        this->renderState = GAMESCREEN;
                        levelsCompleted++;
                        break;
                    } else std::cout << "Already make this level";
                    break;
                }
                else std::cout << "Can't access this level\n";
                break;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
                if(actualLevel().points(&level.level3)) {
                    actualLevel().isPlayerOnMe = false;
                    if (!level.level3.isVisited) {
                        level.level3.isPlayerOnMe = true;
                        game.changeLevel(3);
                        level.level3.isVisited = true;
                        this->renderState = GAMESCREEN;
                        levelsCompleted++;
                        break;
                    } else std::cout << "Already make this level";
                    break;
                }
                else std::cout << "Can't access this level\n";
                break;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
                if(actualLevel().points(&level.level4)) {
                    actualLevel().isPlayerOnMe = false;
                    if (!level.level4.isVisited) {
                        level.level4.isPlayerOnMe = true;
                        game.changeLevel(4);
                        level.level4.isVisited = true;
                        this->renderState = GAMESCREEN;
                        levelsCompleted++;
                        break;
                    } else std::cout << "Already make this level";
                    break;
                }
                else std::cout << "Can't access this level\n";
                break;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                this->renderState = MENUSCREEN;
                saveGame();
                break;
            }
            if(levelsCompleted == 4){
                std::cout << "You Won the Game!!" << std::endl;
                window.close();
            }
            break;
    }
}

void ScreenHandler::render(sf::RenderWindow& window) {
    switch (this->renderState) {
        case GAMESCREEN:
            game.render(window);
            break;
        case MENUSCREEN:
            menu.render(window);
            break;
    }
}


void ScreenHandler::newGame() {
    this->game = Game();
    gameData = GameData(game);

    levelsCompleted = 0;
    level.level1.isVisited = false;
    level.level2.isVisited = false;
    level.level3.isVisited = false;
    level.level4.isVisited = false;
}

void ScreenHandler::loadGame() {
    this->gameData.load("../src/Save/savegame.txt", game, level, levelsCompleted);
    gameData.printScores();

}

void ScreenHandler::saveGame() {
    int kills = this->game.Kills();
    this->gameData.addScore(kills);
    gameData.printScores();

    this->gameData.save("../src/Save/savegame.txt", game, level, levelsCompleted);
}

Node& ScreenHandler::actualLevel() {
    if(game.getLevel() == 1)
        return level.level1;
    if(game.getLevel() == 2)
        return level.level2;
    if(game.getLevel() == 3)
        return level.level3;
    if(game.getLevel() == 4)
        return level.level4;
    throw std::out_of_range("This level doesn't exists\n");
}

