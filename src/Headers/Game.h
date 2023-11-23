#ifndef CMAKESFMLPROJECT_GAME_H
#define CMAKESFMLPROJECT_GAME_H

#include "../States/GameState.h"
#include "../Entities/Enemy.h"

class Game{
protected:
    //Variables
    sf::Texture* playerTexture;
    sf::Texture* enemyTexture;
    sf::Texture* gamesceneTexture;
    sf::RenderWindow* window;
    sf::Event sfEvent;
    sf::Clock dtClock;
    float dt;
    Player* player;
    Enemy* enemy;
    std::stack<State*> states;
    //Initialization
    void initWindow();
    void initStates();

public:

    Game();
    ~Game();

    //Functions
    void endApplication();
    void updateDt();
    void updateSFMLEvents();
    void update();
    void render();
    void run();
    void initTextures();
};


#endif //CMAKESFMLPROJECT_GAME_H
