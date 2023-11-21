
#include "State.h"

State::State(sf::RenderWindow* window) {
    this->window = window;
    this->quit = false;

}

State::~State() {

}

const bool &State::getQuit() const {
    return this->quit;
}

void State::checkForQuit() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        this->quit = true;
}

void State::updateInput(const float &dt) {
        this->checkForQuit();
}

void State::render(sf::RenderTarget *target) {

}