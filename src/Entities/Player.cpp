#include "Player.h"

void Player::initComponents() {

}

void Player::initVariables() {

}

Player::Player(float x, float y, sf::Texture* texture) {
    //this->initVariables();
    //this->initComponents();

    this->createSprite(texture);
    this->setPosition(x, y);
}

Player::~Player() {

}
void Player::Animation(sf::Clock clock) {
    if (notMoving && !isAttacking && !isTakingDamage && !isDead) {
            if (rectSourceSprite.left >= 651)
                rectSourceSprite.left = 0;
            else
                if(cont % 7 == 0)
                    rectSourceSprite.left += 93;

        sprite->setTextureRect(rectSourceSprite);
    }

    if (!notMoving && !isAttacking && !isTakingDamage && !isDead) {

            if(firstTimeWalking){
                rectSourceSprite.left = 744;
                firstTimeWalking = false;
            }

            if (rectSourceSprite.left == 1395)
                rectSourceSprite.left = 744;
            else
                if(cont % 7 == 0)
                    rectSourceSprite.left += 93;
        sprite->setTextureRect(rectSourceSprite);
    }
    else{
        firstTimeWalking = true;
    }


    if(isAttacking &&!isTakingDamage && !isDead){

            if(firstTimeAttacking){
                rectSourceSprite.left = 1488;
                firstTimeAttacking = false;
            }
            if (rectSourceSprite.left == 2325)
                rectSourceSprite.left = 1488;
            else
                if(cont % 7 == 0)
                    rectSourceSprite.left += 93;


            sprite->setTextureRect(rectSourceSprite);
    }
    else{
        firstTimeAttacking = true;
    }


    if(isTakingDamage){

    }

    if(isDead){

    }
    cont++;
}

float Player::getX() const {
    return sprite->getPosition().x;
}

float Player::getY() const {
    return sprite->getPosition().y;
}

bool Player::attack() {
    if(sf::Mouse::isButtonPressed((sf::Mouse::Left))) {
        isAttacking = true;
        return true;
    }
    return false;
}



