
#include "GameState.h"

void GameState::initPlayers() {
    this->player = new Player(0,0, &this->textures["PLAYER"]);
}

GameState::GameState(sf::RenderWindow* window) : State(window){
    this->initPlayers();
}

GameState::~GameState() {
    delete this->player;
}


void GameState::render(sf::RenderTarget* target) {
    if(!target)
        target = this->window;
    this->player->render(target);
}




