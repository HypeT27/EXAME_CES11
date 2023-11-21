
#ifndef CMAKESFMLPROJECT_GAMESTATE_H
#define CMAKESFMLPROJECT_GAMESTATE_H
#include "State.h"

class GameState : public State{
private:
    Player* player;

    void initPlayers();
public:
    GameState(sf::RenderWindow* window);
    ~GameState();


    //Functions
    void render(sf::RenderTarget* target = nullptr);
};


#endif //CMAKESFMLPROJECT_GAMESTATE_H
