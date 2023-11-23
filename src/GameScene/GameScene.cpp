#include "GameScene.h"

GameScene::~GameScene(){
    delete this->Sprite;
}
GameScene::GameScene(const std::string &backgroundFile/*, const std::vector<std::string> &obstacleFiles*/) {
    if (!backgroundTexture.loadFromFile(backgroundFile)) {
        std::cout<<"GameScene ERR";
    }

    backgroundSprite.setTexture(backgroundTexture);

    /*for (const auto& file : obstacleFiles) {
        sf::Texture obstacleTexture;
        if (!obstacleTexture.loadFromFile(file)) {
            return -1
        }
        sf::Sprite obstacleSprite;
        obstacleSprite.setTexture(obstacleTexture);
        obstacleSprites.push_back(obstacleSprite);
    }*/
}

void GameScene::render(sf::RenderWindow &window) {
    window.draw(backgroundSprite);

    /*for (const auto& sprite : obstacleSprites) {
        window.draw(sprite);
    }*/
}


