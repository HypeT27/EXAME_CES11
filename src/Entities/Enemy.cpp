#include "Enemy.h"

Enemy::Enemy(float x, float y, sf::Texture *texture, Player* player) {
    this->movementSpeed = 1.0f;
    stopFollowing = 400;

    stopFollowingShape.setRadius(stopFollowing);
    stopFollowingShape.setOrigin(x,y);

    startShoot = false;

    playerEntity = player;

    this->createSprite(texture);
    this->setPosition(x,y);
}

void Enemy::Update() {
    if(startShoot){

    }
}

void Enemy::followPlayer(sf::Clock clock) {
    playerPos = sf::Vector2f(playerEntity->getX(),playerEntity->getY());
    direction = playerPos  - sprite->getPosition();

    if(sqrt(pow(direction.x-playerPos.x,2) + pow(direction.y-playerPos.y,2)) <= stopFollowing)
        startShoot = true;
    else startShoot = false;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if(length != stopFollowing)
        direction /= length;

    sprite->move(direction * movementSpeed);

}

void Enemy::Animation(sf::Clock clock){
    if (std::abs(direction.x) > std::abs(direction.y)) {
        if (direction.x < 0) {
            if(clock.getElapsedTime().asSeconds() > 1.0f){

                    if (rectSourceSprite.left >= 96)
                        rectSourceSprite.left = 0;
                    else
                        if(cont % 7 == 0)
                            rectSourceSprite.left += 32;


                }
                sprite->setTextureRect(rectSourceSprite);
            }
        else {
            if (clock.getElapsedTime().asSeconds() > 1.0f) {
                if (isLeft) {
                    rectSourceSprite.left = 512;
                    isLeft = false;
                }
                if (rectSourceSprite.left == 608)
                    rectSourceSprite.left = 512;
                else
                    if(cont % 7 == 0)
                        rectSourceSprite.left += 32;

            }
            sprite->setTextureRect(rectSourceSprite);
        }
    }
    else {
        if (direction.y > 0) {
            if (clock.getElapsedTime().asSeconds() > 1.0f) {
                if (isDown) {
                    rectSourceSprite.left = 128;
                    isDown = false;
                }
                if (rectSourceSprite.left == 224)
                    rectSourceSprite.left = 128;
                else
                    if(cont % 7 == 0)
                        rectSourceSprite.left += 32;

            }
            sprite->setTextureRect(rectSourceSprite);

        }
        if (direction.y < 0){
            if (clock.getElapsedTime().asSeconds() > 1.0f) {
                if (isUp) {
                    rectSourceSprite.left = 640;
                    isUp = false;
                }
                if (rectSourceSprite.left == 736)
                    rectSourceSprite.left = 640;
                else
                    if(cont % 7 == 0)
                        rectSourceSprite.left += 32;

            }
            sprite->setTextureRect(rectSourceSprite);
        }
    }
    cont++;
}

void Enemy::createSprite(sf::Texture *texture) {
    this->texture = texture;
    this->sprite = new sf::Sprite(*this->texture, rectSourceSprite);
}












