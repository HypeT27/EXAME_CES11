//
// Created by gabri on 04/12/2023.
//

#include "LevelState.h"

LevelState::LevelState() {
    map = new sf::Sprite();
    mapTexture = new sf::Texture();

    setValues();
}

void LevelState::setValues() {
    map->setPosition(0,0);

    map->setTexture(*mapTexture);

    level1.defineLevel(1);
    level2.defineLevel(2);
    level3.defineLevel(3);
    level4.defineLevel(4);

    level1.addNode(&level2);
    level2.addNode(&level3);
    level2.addNode(&level4);
    level3.addNode(&level4);
    level4.addNode(&level3);
}

void LevelState::render(sf::RenderWindow &window) {
    window.clear();
    window.draw(*map);
    window.display();
}

void LevelState::update(sf::RenderWindow &window) {
    while(window.pollEvent(this->sfEvent))
        if(this->sfEvent.type == sf::Event::Closed)
            window.close();
}
