#ifndef EXAME_CES11_PLAYER_H
#define EXAME_CES11_PLAYER_H
#include "Entity.h"



class Player : public Entity{
private:
    float totalElapsedTime = 0.0f;
    float animationInterval = 50.f;
    bool firstTimeWalking = true;
    bool firstTimeAttacking = true;
    sf::IntRect rectSourceSprite{0, 0, 93, 58};
    void initVariables();
    void initComponents();
public:
    Player(float x, float y, sf::Texture* texture);
    ~Player();
    float getX() const;
    float getY() const;

    void Animation(sf::Clock clock);
};


#endif //EXAME_CES11_PLAYER_H
