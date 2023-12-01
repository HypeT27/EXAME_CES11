
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
    if(newBullet)
        direction = getDirection();

    newBullet = false;
    sprite->move(direction * movementSpeed);
}

void enemyBullet::serialize(FILE* file){

    if (this == nullptr) {
        std::cout << "Jogador nulo\n";
        return;
    }

    if (this->sprite == nullptr) {
        std::cout << "Sprite nulo\n";
        return;
    }

    sf::Vector2f Direction = getDirection();
    sf::Vector2f position = sprite->getPosition();

    float x2Value = Direction.x;
    float y2Value = Direction.y;

    float x1Value = position.x;
    float y1Value = position.y;


    fprintf(file, "%f\n", x1Value);
    fprintf(file, "%f\n", y1Value);

    fprintf(file, "%f\n", x2Value);
    fprintf(file, "%f\n", y2Value);
}

void enemyBullet::deserialize(FILE* file) {
    float x2Value;
    float y2Value;
    float x1Value;
    float y1Value;

    fscanf(file, "%f", &x1Value);
    fscanf(file, "%f", &y1Value);

    fscanf(file, "%f", &x2Value);
    fscanf(file, "%f", &y2Value);

    this->setPosition(x1Value, y1Value);
    this->setDirection(x2Value, y2Value);
}

sf::Vector2f enemyBullet::getDirection() {
    sf::Vector2f playerPos = sf::Vector2f(x2, y2);
    direction = playerPos - sf::Vector2f(x1,y1);
    auto length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction = direction/length;
    return direction;
}

void enemyBullet::setDirection(float x, float y) {
    x1 = 0;
    y1 = 0;

    x2 = x;
    y2 = y;
}


