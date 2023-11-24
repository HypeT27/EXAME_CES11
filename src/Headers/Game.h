#ifndef CMAKESFMLPROJECT_GAME_H
#define CMAKESFMLPROJECT_GAME_H

#include "../States/GameState.h"
#include "../Entities/Enemy.h"
#include "../GameScene/GameScene.h"
#include "../Entities/enemyBullet.h"
#include "../Entities//playerAttack.h"

class Game{
protected:
    int enemiesCounter = 2;
    sf::Texture* playerTexture;
    sf::Texture* enemyTexture;
    sf::Texture* gamesceneTexture;
    sf::RenderWindow* window;
    sf::Event sfEvent;
    sf::Clock dtClock;
    sf::Time dt;

    Player* player;
    Enemy* enemy;
    Enemy* enemy2;
    GameScene* gamescene;
    std::vector<Enemy*> aliveEnemies;
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
