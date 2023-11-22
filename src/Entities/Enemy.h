//
// Created by gabri on 21/11/2023.
//

#ifndef EXAME_CES11_ENEMY_H
#define EXAME_CES11_ENEMY_H

#include "Entity.h"
#include "Player.h"

class Enemy : public Entity{
private:
    int cont = 0;
    sf::IntRect rectSourceSprite{0, 0, 32, 32};
    sf::Vector2f direction;
    sf::CircleShape stopFollowingShape;

    float stopFollowing;

    bool isUp = true;
    bool isLeft = true;
    bool isDown = true;

    bool startShoot = false;

    sf::Vector2f playerPos;
    Player* playerEntity;

public:
    Enemy(float x, float y, sf::Texture* texture, Player* player);
    void Update();
    void followPlayer(sf::Clock clock);
    void Animation(sf::Clock clock);
    void createSprite(sf::Texture* texture) override;
};


#endif //EXAME_CES11_ENEMY_H
