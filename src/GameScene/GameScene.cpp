#include "GameScene.h"

GameScene::~GameScene(){
    delete this->backgroundTexture;
    delete this->backgroundSprite;
}

GameScene::GameScene(int posic_x, int posic_y, sf::Texture *texture) {
    this->backgroundTexture = texture;

    this->posic_x = posic_x;
    this->posic_y = posic_y;
//SE EU DER RUN RODA PRA VC TBM? sim
    sf::IntRect rectSourceSprite (this->posic_x, this->posic_y, 800, 600);
    this->backgroundSprite = new sf::Sprite (*this->backgroundTexture, rectSourceSprite);

    this->lchild = nullptr;
    this->rchild = nullptr;
}

void GameScene::render(sf::RenderTarget& window) {
    window.draw(*this->backgroundSprite);

}


