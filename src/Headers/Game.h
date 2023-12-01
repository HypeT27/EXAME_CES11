#ifndef CMAKESFMLPROJECT_GAME_H
#define CMAKESFMLPROJECT_GAME_H

#include "../Entities/Enemy.h"
#include "../GameScene/GameSceneTree.h"
#include "../Entities/enemyBullet.h"
#include "../Entities//playerAttack.h"
#include "../States/MenuState.h"

class Game{
protected:
    int enemiesCounter;
    int killCounter = 0;

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
    sf::Texture* bulletTexture;

    sf::Event sfEvent;
    sf::Clock dtClock;
    sf::Time dt;

    Player* player;
    GameSceneTree* gameSceneTree;
    GameScene* gamescene;

    std::vector<Enemy*> aliveEnemies;

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

    void initTextures();

public:
    int Kills();

    Game();
    ~Game();

    //Functions
    void updateDt();
    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    Player* getPlayer() const;
    std::vector<Enemy*> getEnemies();
    std::vector<enemyBullet *> getBullets() const;
    void addBullet();


};


#endif //CMAKESFMLPROJECT_GAME_H
