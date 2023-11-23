//
// Created by gabri on 22/11/2023.
//

#ifndef EXAME_CES11_ENEMYBULLET_H
#define EXAME_CES11_ENEMYBULLET_H
#include "Entity.h"
#include "Player.h"

class enemyBullet : public Entity {
private:
    int cont = 0;
    sf::IntRect rectSourceSprite{0, 0, 26, 26};
    bool newBullet = true;
    sf::Vector2f direction;
    Player* playerEntity;
public:
    void Animation();
    enemyBullet(float x, float y, sf::Texture* texture, Player* player);
    ~enemyBullet();
    void createSprite(sf::Texture *texture) override;
    void followDirection();
};


#endif //EXAME_CES11_ENEMYBULLET_H
