
#include "enemyBullet.h"

enemyBullet::enemyBullet(float x, float y, sf::Texture* texture, Player* player) {
    this->createSprite(texture);
    this->setPosition(x,y);

    playerEntity = player;
    this->movementSpeed = 2.f;
}

enemyBullet::~enemyBullet() {
    delete this->sprite;
    delete this->playerEntity;
}

void enemyBullet::createSprite(sf::Texture *texture) {
    this->texture = texture;
    this->sprite = new sf::Sprite(*this->texture, rectSourceSprite);
}

void enemyBullet::Animation() {
    if (rectSourceSprite.left >= 78) {
        rectSourceSprite.left = 0;
    }
    else
        if(cont % 10 == 0)
            rectSourceSprite.left += 26;
    sprite->setTextureRect(rectSourceSprite);
    cont++;
}

void enemyBullet::followDirection() {
    if(newBullet) {
        sf::Vector2f playerPos = sf::Vector2f(playerEntity->getX(), playerEntity->getY());
        direction = playerPos - sprite->getPosition();
        auto length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction = direction/length;
    }
    newBullet = false;
    sprite->move(direction * movementSpeed);
}

