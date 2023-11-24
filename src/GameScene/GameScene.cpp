#include "GameScene.h"

GameScene::~GameScene(){
    delete this->backgroundTexture;
    delete this->backgroundSprite;

}
GameScene::GameScene(int posic_x, int posic_y, sf::Texture *texture) {
    this->backgroundTexture = texture;

    sf::IntRect rectSourceSprite (posic_x, posic_y, 800, 600);
    this->backgroundSprite = new sf::Sprite (*this->backgroundTexture, rectSourceSprite);
}

void GameScene::render(sf::RenderTarget* window) {
    window->draw(*this->backgroundSprite);

}


