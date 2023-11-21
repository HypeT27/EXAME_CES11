#include "Player.h"
void Player::initComponents() {

}

void Player::initVariables() {

}

Player::Player(float x, float y, sf::Texture* texture) {
    this->initVariables();
    this->initComponents();

    this->createSprite(texture);
    this->setPosition(x, y);
}

Player::~Player() {

}
void Player::Animation(sf::Clock clock) {
    if (notMoving && !isAttacking && !isTakingDamage && !isDead) {

        if(clock.getElapsedTime().asSeconds()> 1.0f){

            if (rectSourceSprite.left >= 651)
                rectSourceSprite.left = 0;
            else
                rectSourceSprite.left += 93;

        }
        sprite->setTextureRect(rectSourceSprite);
    }

    if (!notMoving && !isAttacking && !isTakingDamage && !isDead) {

        if(clock.getElapsedTime().asSeconds() > 1.0f) {
            if(firstTimeWalking){
                rectSourceSprite.left = 744;
                firstTimeWalking = false;
            }
            if (rectSourceSprite.left == 1395)
                rectSourceSprite.left = 744;
            else
                rectSourceSprite.left += 93;

            totalElapsedTime -= animationInterval;
        }
        sprite->setTextureRect(rectSourceSprite);
    }
    else{
        firstTimeWalking = true;
    }
    if(isAttacking &&!isTakingDamage && !isDead){


    }
    if(isTakingDamage){

    }

    if(isDead){

    }
    clock.restart();
}

