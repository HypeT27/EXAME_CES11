#ifndef EXAME_CES11_PLAYER_H
#define EXAME_CES11_PLAYER_H

#include "Entity.h"
#include <string>

class playerAttack;

class Player : public Entity{
private:
    int cont = 0;
    bool canDash = true;
    bool canAttack = true;

    sf::CircleShape hitBox;

    sf::Time attackTimer;
    sf::Time attackCD = sf::seconds((1.0f));
    sf::Time dashTimer;
    sf::Time dashCD = sf::seconds(2.0f);

    bool firstTimeMoving = true;
    bool firstTimeWalking = true;
    bool firstTimeAttacking = true;
    sf::IntRect rectSourceSprite{0, 0, 38, 38};

    sf::Texture* attackTexture;

    void initTextures();
public:
    Player(float x, float y, sf::Texture* texture);
    ~Player();

    void setPosition(float x, float y) override;
    void update(sf::Time dt);
    void Animation(std::vector<playerAttack*>& activeAttacks);
    void Dash();
    bool checkDamage(const Entity* entity);

    void serialize(FILE* file) const;

    void deserialize(FILE* file);
};


#endif //EXAME_CES11_PLAYER_H
