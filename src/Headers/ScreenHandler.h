//
// Created by gabri on 29/11/2023.
//

#ifndef EXAME_CES11_SCREENHANDLER_H
#define EXAME_CES11_SCREENHANDLER_H

#include "../Entities/Entity.h"
#include "Game.h"
#include "../States/MenuState.h"
#include "../Save/GameData.h"
#include "../States/LevelState.h"

#define MENUSCREEN 0
#define GAMESCREEN 1
#define LEVELSCREEN 2

class ScreenHandler {
public:
    Game game;
    GameData gameData;
    MenuState menu;

    LevelState level;


    explicit ScreenHandler();

    void render(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
    void printTimes(std::vector<float>&);
    void updateTime();
    void deleteLastFloat(const std::string& fileName);

    void loadGame();
    void newGame();
    void saveGame();

    Node& actualLevel();

    int renderState = 0;
    int levelsCompleted = 0;
private:
    sf::Time gameTotalTime;
    sf::Clock gameClock;
};


#endif //EXAME_CES11_SCREENHANDLER_H
