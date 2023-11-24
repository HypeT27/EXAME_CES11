#ifndef EXAME_CES11_GAMESCENE_H
#define EXAME_CES11_GAMESCENE_H
#include "../Entities/Entity.h"
#include <vector>
#include <string>

class GameScene {
private:
    sf::Texture* backgroundTexture;
    sf::Sprite* backgroundSprite;

public:
    GameScene(int posic_x, int posic_y, sf::Texture *texture);
    ~GameScene();

    void render(sf::RenderTarget* window);
};


#endif //EXAME_CES11_GAMESCENE_H
