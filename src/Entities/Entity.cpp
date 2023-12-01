
#include "Entity.h"


Entity::Entity() {
    this->sprite = nullptr;
    this->texture = nullptr;
    this->movementSpeed = 2.0f;
}

Entity::~Entity() {
}

void Entity::createSprite(sf::Texture* texture) {
    this->texture = texture;
    sf::IntRect rectSourceSprite(0,0,38,38);
    this->sprite = new sf::Sprite(*this->texture, rectSourceSprite);
}

void Entity::setPosition(float x, float y) {
    if(this->sprite)
        this->sprite->setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y) {
    if (this->sprite) {
        this->sprite->move(dir_x * this->movementSpeed, dir_y * this->movementSpeed);
    }
}

void Entity::render(sf::RenderTarget& target) {
    target.draw(*this->sprite);
}

float Entity::getX() const {
    return (sprite != nullptr) ? sprite->getPosition().x : 0.0f;
}

float Entity::getY() const {
    if(sprite) {
        return sprite->getPosition().y;
    }
    else throw std::runtime_error("Sprite nulo");
}


