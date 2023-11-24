#include "Enemy.h"

void Enemy::initTextures() {
    this->bulletTexture = new sf::Texture;
    this->bulletTexture->loadFromFile("../src/Images/enemyBullet.png");
}


Enemy::Enemy(float x, float y, sf::Texture *texture, Player* player) {
    this->createSprite(texture);
    this->setPosition(x,y);
    
    initTextures();

    this->movementSpeed = 0.5f;
    stopFollowing = 300;

    stopFollowingShape.setRadius(stopFollowing);
    stopFollowingShape.setOrigin(x,y);

    startShoot = false;

    playerEntity = player;

    hitBox.setRadius(16);
    hitBox.setPosition(this->getX(), this->getY());

}

Enemy::~Enemy() {

}

void Enemy::attack(std::vector<enemyBullet*>& activeBullets) {
        if (startShoot) {
                if (rectSourceSprite.left >= 448) {
                    auto pBullet = new enemyBullet(this->getX(), this->getY(), bulletTexture, playerEntity);
                    activeBullets.push_back(pBullet);
                    rectSourceSprite.left = 256;
                } else if (contAttack % 6 == 0)
                    rectSourceSprite.left += 32;
            }
            if (contAttack % 5 == 0)
                sprite->setTextureRect(rectSourceSprite);
        contAttack++;
    }


void Enemy::followPlayer() {
        playerPos = sf::Vector2f(playerEntity->getX(), playerEntity->getY());
        direction = playerPos - sprite->getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != stopFollowing)
            direction /= length;

        if (length < stopFollowing)
            startShoot = true;
        else {
            startShoot = false;
            sprite->move(direction * movementSpeed);
        }
}

void Enemy::Animation(sf::Clock clock) {
    if (!startShoot) {
        if (std::abs(direction.x) > std::abs(direction.y)) {
            if (direction.x < 0) {
                if (clock.getElapsedTime().asSeconds() > 1.0f) {

                    if (rectSourceSprite.left >= 96)
                        rectSourceSprite.left = 0;
                    else if (cont % 7 == 0)
                        rectSourceSprite.left += 32;

                }
                sprite->setTextureRect(rectSourceSprite);
            } else {
                if (clock.getElapsedTime().asSeconds() > 1.0f) {
                    if (isLeft) {
                        rectSourceSprite.left = 512;
                        isLeft = false;
                    }
                    if (rectSourceSprite.left == 608)
                        rectSourceSprite.left = 512;
                    else if (cont % 7 == 0)
                        rectSourceSprite.left += 32;

                }
                sprite->setTextureRect(rectSourceSprite);
            }
        } else {
            if (direction.y > 0) {
                if (clock.getElapsedTime().asSeconds() > 1.0f) {
                    if (isDown) {
                        rectSourceSprite.left = 128;
                        isDown = false;
                    }
                    if (rectSourceSprite.left == 224)
                        rectSourceSprite.left = 128;
                    else if (cont % 7 == 0)
                        rectSourceSprite.left += 32;

                }
                sprite->setTextureRect(rectSourceSprite);

            }
            if (direction.y < 0) {
                if (clock.getElapsedTime().asSeconds() > 1.0f) {
                    if (isUp) {
                        rectSourceSprite.left = 640;
                        isUp = false;
                    }
                    if (rectSourceSprite.left == 736)
                        rectSourceSprite.left = 640;
                    else if (cont % 7 == 0)
                        rectSourceSprite.left += 32;

                }
                sprite->setTextureRect(rectSourceSprite);
            }
        }
        cont++;
    }
}

void Enemy::createSprite(sf::Texture *texture) {
    this->texture = texture;
    this->sprite = new sf::Sprite(*this->texture, rectSourceSprite);
}

bool Enemy::checkDamage(const Entity* entity) {
    hitBox.setPosition(this->getX(),this->getY());
    auto distance = sqrt(pow(this->getX()-entity->getX(),2)+pow(this->getY()-entity->getY(),2));
    if(distance <= hitBox.getRadius()){
        return true;
    }
    return false;
}

int Enemy::hitCount() const {
    return this->hitCounter;
}

int Enemy::hitCountAdd() {
    return ++hitCounter;
}












