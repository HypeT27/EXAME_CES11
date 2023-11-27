#ifndef CMAKESFMLPROJECT_GAME_H
#define CMAKESFMLPROJECT_GAME_H

#include "../States/GameState.h"
#include "../Entities/Enemy.h"
#include "../GameScene/GameScene.h"
#include "../Entities/enemyBullet.h"
#include "../Entities//playerAttack.h"
#include "../States/MenuState.h"

class Game{
protected:

    int hitCounter = 0;
    sf::Texture* playerTexture;
    sf::Texture* enemyTexture;
    sf::Texture* gamesceneTexture;
    sf::Texture* estradaTexture;
    sf::Texture* lakeTexture;
    sf::Texture* tree1Texture;
    sf::Texture* tree2Texture;
    sf::Texture* tree3Texture;
    sf::Texture* tree4Texture;
    sf::Texture* cactusTexture;
    sf::Texture* stoneTexture;

    sf::RenderWindow* window;
    sf::Event sfEvent;
    sf::Clock dtClock;
    sf::Time dt;

    Player* player;
    Enemy* enemy;
    GameScene* gamescene;
    GameScene* estrada;
    GameScene* lake;
    GameScene* tree1;
    GameScene* tree2;
    GameScene* tree3;
    GameScene* tree4;
    GameScene* cactus;
    GameScene* stone;



    std::vector<enemyBullet*> activeBullets;
    std::vector<playerAttack*> activeAttacks;

    std::stack<State*> states;

    void initWindow();
    void initStates();
    void initTextures();

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

};


#endif //CMAKESFMLPROJECT_GAME_H
