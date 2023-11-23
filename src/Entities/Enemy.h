
#ifndef EXAME_CES11_ENEMY_H
#define EXAME_CES11_ENEMY_H

#include "Entity.h"
#include "Player.h"
#include "enemyBullet.h"

class Enemy : public Entity{
private:
    int cont = 0;
    int contAttack = 0;
    sf::IntRect rectSourceSprite{0, 0, 32, 32};
    sf::Vector2f direction;
    sf::CircleShape stopFollowingShape;

    sf::CircleShape hitBox;
    sf::Texture* bulletTexture;

    float stopFollowing;

    bool startShoot = false;

    sf::Vector2f playerPos;
    Player* playerEntity;

    void initTextures();

public:
    ~Enemy();
    Enemy(float x, float y, sf::Texture* texture, Player* player);
    void attack(std::vector<enemyBullet*>& activeBullets);
    void followPlayer();
    void Animation(sf::Clock clock);
    void createSprite(sf::Texture* texture) override;
    bool checkDamage(const Entity* entity);
};


#endif //EXAME_CES11_ENEMY_H
