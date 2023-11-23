//
// Created by gabri on 23/11/2023.
//

#include "playerAttack.h"


playerAttack::playerAttack(float x, float y, sf::Texture *texture) {
    this->createSprite(texture);
    this->setPosition(x,y);

    this->movementSpeed = 10.f;
}

playerAttack::~playerAttack() {
    delete this->sprite;
    delete this->playerEntity;
}

void playerAttack::createSprite(sf::Texture *texture) {
    this->texture = texture;
    this->sprite = new sf::Sprite(*this->texture, rectSourceSprite);
}

void playerAttack::followDirection(sf::RenderWindow* window) {
    if(newAttack) {
        sf::Vector2f cursorPosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
        sf::Vector2f entityPosition = sprite->getPosition();

        direction = cursorPosition - entityPosition;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length != 0) {
            direction /= length;
        }
    }

    newAttack = false;
    sprite->move(direction * movementSpeed);
}

