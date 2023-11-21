#ifndef EXAME_CES11_PLAYER_H
#define EXAME_CES11_PLAYER_H
#include "Entity.h"


class Player : public Entity{
private:
    float totalElapsedTime = 0.0f;
    float animationInterval = 50.f;
    bool firstTimeWalking = true;
    sf::IntRect rectSourceSprite{0, 0, 93, 58};
    void initVariables();
    void initComponents();
public:
    Player(float x, float y, sf::Texture* texture);
    ~Player();

    void Animation(sf::Clock clock);
};


#endif //EXAME_CES11_PLAYER_H
