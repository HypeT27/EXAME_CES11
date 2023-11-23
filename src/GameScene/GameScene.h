#ifndef EXAME_CES11_GAMESCENE_H
#define EXAME_CES11_GAMESCENE_H
#include "../Entities/Entity.h"
#include <vector>
#include <string>

class GameScene {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    std::vector<sf::Sprite> obstacleSprites;

public:
    GameScene(const std::string& backgroundFile/*, const std::vector<std::string>& obstacleFiles*/);
    void draw(sf::RenderWindow& window);
};


#endif //EXAME_CES11_GAMESCENE_H
