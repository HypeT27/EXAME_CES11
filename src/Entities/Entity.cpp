
#include "Entity.h"

void Entity::initVariables() {
    this->sprite = nullptr;
    this->texture = nullptr;
    this->movementSpeed = 2.0f;
}

Entity::Entity() {
    this->initVariables();
}

Entity::~Entity() {
    delete this->sprite;
}

void Entity::createSprite(sf::Texture* texture) {
    this->texture = texture;
    sf::IntRect rectSourceSprite(0,0,93,58);
    this->sprite = new sf::Sprite(*this->texture, rectSourceSprite);
}

void Entity::setPosition(const float x, const float y) {
    if(this->sprite)
        this->sprite->setPosition(x, y);
}


void Entity::move(const float& dt, float dir_x, const float dir_y) {
    if (this->sprite) {
        this->sprite->move(dir_x * this->movementSpeed, dir_y * this->movementSpeed);
    }
}

void Entity::update(const float& dt) {
    notMoving = true;
    isAttacking = false;
    if (sf::Keyboard::isKeyPressed((sf::Keyboard::A)) ||
        sf::Keyboard::isKeyPressed((sf::Keyboard::Left))) {
        this->move(dt, -1.f, 0.f);
        notMoving = false;
    }
    if (sf::Keyboard::isKeyPressed((sf::Keyboard::S)) ||
            sf::Keyboard::isKeyPressed((sf::Keyboard::Down))){
            this->move(dt, 0.f, 1.f);
            notMoving = false;
    }
    if (sf::Keyboard::isKeyPressed((sf::Keyboard::W)) ||
            sf::Keyboard::isKeyPressed((sf::Keyboard::Up))){
            this->move(dt, 0.f, -1.f);
            notMoving = false;
    }
    if (sf::Keyboard::isKeyPressed((sf::Keyboard::D)) ||
            sf::Keyboard::isKeyPressed((sf::Keyboard::Right))){
            this->move(dt, 1.f, 0.f);
            notMoving = false;
    }
}

void Entity::render(sf::RenderTarget* target) {
    if (this->sprite)
        target->draw(*this->sprite);

}


