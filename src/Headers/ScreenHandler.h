//
// Created by gabri on 29/11/2023.
//

#ifndef EXAME_CES11_SCREENHANDLER_H
#define EXAME_CES11_SCREENHANDLER_H

#include "../Entities/Entity.h"
#include "Game.h"
#include "../States/MenuState.h"
#include "../Save/GameData.h"

#define MENUSCREEN 0
#define GAMESCREEN 1

class ScreenHandler {
public:
    Game game;
    GameData gameData;
    MenuState menu;
    explicit ScreenHandler();

    void render(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);

    //pra fz o save dps
    void loadGame();
    void newGame();
    void saveGame();

    void gameStart(sf::RenderWindow& window);

    int renderState = 0;

};


#endif //EXAME_CES11_SCREENHANDLER_H
