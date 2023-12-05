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
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                if (actualLevel().points(&level.level1)) {
                    if (!level.level1.isVisited) {
                        level.level1.isPlayerOnMe = true;
                        game.changeLevel(1);
                        level.level1.isVisited = true;
                        this->renderState = GAMESCREEN;
                        levelsCompleted++;
                        break;
                    } else std::cout << "Already make this level";
                    break;
                }
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
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
                if(actualLevel().points(&level.level5)) {
                    actualLevel().isPlayerOnMe = false;
                    if (!level.level5.isVisited) {
                        level.level5.isPlayerOnMe = true;
                        game.changeLevel(5);
                        level.level5.isVisited = true;
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
            if(levelsCompleted == 5) {
                std::cout << "You Won the Game!!" << std::endl;
                gameTotalTime += gameClock.getElapsedTime();
                std::cout << "Time to complete the game: " << gameTotalTime.asSeconds() << " segundos" << std::endl;
                gameData.saveTime("../src/Save/savetimes.txt",gameTotalTime);
                printTimes(gameData.existentTimes);
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
        case LEVELSCREEN:
            level.render(window);
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
    gameClock.restart();
    std::cout << "Creating New Game.. \n";
}

void ScreenHandler::loadGame() {
    updateTime();

    this->gameData.load("../src/Save/savegame.txt", game, level, levelsCompleted);
    std::cout << "Game Loaded!! \n";
}

void ScreenHandler::saveGame() {
    gameTotalTime += gameClock.getElapsedTime();
    gameData.saveTime("../src/Save/savetimes.txt",gameTotalTime);
    this->gameData.save("../src/Save/savegame.txt", game, level, levelsCompleted);
    std::cout << "Saved Successfully!!\n";
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
    if(game.getLevel() == 5)
        return level.level5;
    throw std::out_of_range("This level doesn't exists\n");
}

void ScreenHandler::printTimes(std::vector<float>& existentTimes) {
    gameData.rankingTimes(existentTimes);
    std::cout << "Top 6 World Ranking: \n";
    std::cout << "---------------\n";
    for(int i = 0; i < existentTimes.size(); i++)
        std::cout << i + 1 << ": " << existentTimes[i] << std::endl;
    std::cout << "---------------\n";
}

void ScreenHandler::updateTime() {
    std::vector<float> savedTimes = this->gameData.loadTime("../src/Save/savetimes.txt");

    float lastSavedTimeFloat = this->gameData.getLastTime(savedTimes);
    deleteLastFloat("../src/save/savetimes.txt");


    sf::Time lastSavedTime  = sf::seconds(lastSavedTimeFloat);
    gameTotalTime += lastSavedTime;
}

void ScreenHandler::deleteLastFloat(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    std::vector<float> floats;

    if (inputFile.is_open()) {
        float value;

        while (inputFile >> value) {
            floats.push_back(value);
        }

        inputFile.close();

        if (!floats.empty()) {
            floats.pop_back();
        }

        std::ofstream outputFile(fileName);
        for (const float& newValue : floats) {
            outputFile << newValue << '\n';
        }

        std::cout << "Ultimo float removido com sucesso." << std::endl;
    }
    else std::cerr << "Erro ao abrir o arquivo." << std::endl;
}


