#include "GameScene.h"

GameScene::~GameScene(){
    delete this->backgroundSprite;
    delete this->backgroundTexture;
}
GameScene::GameScene(float x, float y, sf::Texture *texture) {
    /*if (!backgroundTexture->loadFromFile(backgroundFile)) {
        std::cout<<"GameScene ERR";
    }*/
    this->backgroundTexture = texture;
    sf::IntRect rectSourceSprite (0, 0, 800, 600);
    this->backgroundSprite = new sf::Sprite (*this->backgroundTexture, rectSourceSprite);

    //backgroundSprite->setTexture(*backgroundTexture);

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

void GameScene::render(sf::RenderTarget* window) {
    window->draw(*this->backgroundSprite);

    /*for (const auto& sprite : obstacleSprites) {
        window.draw(sprite);
    }*/
}


