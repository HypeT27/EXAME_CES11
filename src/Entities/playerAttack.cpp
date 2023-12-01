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

void playerAttack::followDirection(sf::RenderWindow& window) {
    if(newAttack)
       direction = getDirection(window);

    newAttack = false;
    sprite->move(direction * movementSpeed);
}



void playerAttack::serialize(FILE* file){

    if (this == nullptr) {
        std::cout << "Jogador nulo\n";
        return;
    }

    if (this->sprite == nullptr) {
        std::cout << "Sprite nulo\n";
        return;
    }

    sf::Vector2f position = sprite->getPosition();

    float xValue = position.x;
    float yValue = position.y;


    fprintf(file, "%f\n", xValue);
    fprintf(file, "%f\n", yValue);
}

void playerAttack::deserialize(FILE* file) {
    float xValue;
    float yValue;
    fscanf(file, "%f", &xValue);
    fscanf(file, "%f", &yValue);

    this->setPosition(xValue, yValue);
}

sf::Vector2f playerAttack::getDirection(sf::RenderWindow& window) {
    sf::Vector2f cursorPosition = sf::Vector2f(sf::Mouse::getPosition(window));
    sf::Vector2f entityPosition = sprite->getPosition();

    direction = cursorPosition - entityPosition;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0)
        direction /= length;

    return direction;
}

void playerAttack::setDirection(float x, float y) {
    x1 = 0;
    y1 = 0;

    x2 = x;
    y2 = y;
}
