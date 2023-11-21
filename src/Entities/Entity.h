//
// Created by gabri on 20/11/2023.
//

#ifndef CMAKESFMLPROJECT_ENTITY_H
#define CMAKESFMLPROJECT_ENTITY_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Entity {
private:
    void initVariables();
protected:
    sf::Texture* texture;
    sf::Sprite* sprite;
    bool notMoving = true;
    bool isAttacking = false;
    bool isTakingDamage = false;
    bool isDead = false;


public:
    float movementSpeed;
    Entity();
    ~Entity();

    virtual void createSprite(sf::Texture* texture);

    void setPosition(const float x, const float y);
    void move(const float& dt, float x, float y);

    void update(const float& dt);
    void render(sf::RenderTarget* target);

};


#endif //CMAKESFMLPROJECT_ENTITY_H
