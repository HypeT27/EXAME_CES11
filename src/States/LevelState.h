//
// Created by gabri on 04/12/2023.
//

#ifndef EXAME_CES11_LEVELSTATE_H
#define EXAME_CES11_LEVELSTATE_H
#include "../Entities/Entity.h"
#include "../Node/Node.h"

class LevelState {
private:
    sf::Sprite* map;
    sf::Texture* mapTexture;

    sf::Event sfEvent;

public:
    Node level1;
    Node level2;
    Node level3;
    Node level4;
    Node level5;

    LevelState();
    void setValues();
    void setTexture();
    void render(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
};


#endif //EXAME_CES11_LEVELSTATE_H
