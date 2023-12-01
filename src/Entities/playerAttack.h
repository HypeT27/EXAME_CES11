//
// Created by gabri on 23/11/2023.
//

#ifndef EXAME_CES11_PLAYERATTACK_H
#define EXAME_CES11_PLAYERATTACK_H
#include "Entity.h"
#include "Player.h"

class playerAttack : public Entity{
private:
    sf::Vector2f direction;
    bool newAttack = true;
    Player* playerEntity;
    sf::IntRect rectSourceSprite{0, 0, 32, 30};
public:
    float x1,y1,x2,y2;
    playerAttack(float x, float y, sf::Texture* texture);
    ~playerAttack();
    void createSprite(sf::Texture *texture) override;
    void followDirection(sf::RenderWindow& window);

    void serialize(FILE* file);
    void deserialize(FILE* file);

    sf::Vector2f getDirection(sf::RenderWindow& window);
    void setDirection(float x, float y);
};


#endif //EXAME_CES11_PLAYERATTACK_H
