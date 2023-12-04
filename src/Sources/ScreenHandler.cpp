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
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                this->renderState = MENUSCREEN;
                saveGame();
                break;
            }
            break;
        case MENUSCREEN:
            menu.update(window);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                this->renderState = GAMESCREEN;
                newGame();
                break;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
                this->renderState = GAMESCREEN;
                loadGame();
                break;
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
}

void ScreenHandler::loadGame() {
    gameData.printScores();
    this->gameData.load("../src/Save/savegame.txt", game);
}

void ScreenHandler::saveGame() {
    int kills = this->game.Kills();
    this->gameData.addScore(kills);
    gameData.printScores();

    this->gameData.save("../src/Save/savegame.txt", game);
}

