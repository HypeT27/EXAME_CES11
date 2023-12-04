//
// Created by gabri on 20/11/2023.
//

#ifndef CMAKESFMLPROJECT_ENTITY_H
#define CMAKESFMLPROJECT_ENTITY_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <memory>
#include <map>
#include <vector>
#include <cmath>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>



class Entity {
protected:
    sf::Texture* texture;
    sf::Sprite* sprite;

    bool notMoving = true;
    bool isAttacking = false;
    bool isTakingDamage = false;
    bool isDead = false;

    bool isLeft = false;
    bool isDown = false;
    bool isUp = false;
    bool isRight = false;

public:
    float movementSpeed{};
    Entity();
    ~Entity();

    virtual void createSprite(sf::Texture* texture);

    virtual void setPosition(float x, float y);
    void move(float x, float y);

    void render(sf::RenderTarget& target);

    float getX() const;
    float getY() const;
};


#endif //CMAKESFMLPROJECT_ENTITY_H
