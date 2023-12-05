#ifndef CMAKESFMLPROJECT_GAME_H
#define CMAKESFMLPROJECT_GAME_H

#include "../Entities/Enemy.h"
#include "../GameScene/GameSceneTree.h"
#include "../Entities/enemyBullet.h"
#include "../Entities//playerAttack.h"
#include "../States/MenuState.h"

class Game{
protected:
    int level = 1;
    int enemiesCounter = 0;
    int killCounter = 0;

    sf::Texture* playerTexture;
    sf::Texture* enemyTexture;


    sf::Texture* fundolevel1Texture;
    sf::Texture* fundolevel2Texture;
    sf::Texture* fundolevel3Texture;
    sf::Texture* fundolevel4Texture;
    sf::Texture* fundolevel5Texture;


    sf::Texture* bulletTexture;

    sf::Event sfEvent;
    sf::Clock dtClock;
    sf::Time dt;

    Player* player;
    Enemy* enemy;

    GameSceneTree* gameSceneTree;

    std::vector<Enemy*> aliveEnemies;

    std::vector<enemyBullet*> activeBullets;
    std::vector<playerAttack*> activeAttacks;

    void initTextures();
    void initEnemies();

public:
    Game();
    ~Game();

    //Functions
    void updateDt();
    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    Player* getPlayer() const;
    std::vector<Enemy*> getEnemies();
    int getEnemiesCounter() const;

    std::vector<enemyBullet *> getBullets() const;
    void addBullet();

    void nextLevel();
    int getLevel();
    void changeLevel(int level);
    void changeEnemyCounter(int);

};


#endif //CMAKESFMLPROJECT_GAME_H
