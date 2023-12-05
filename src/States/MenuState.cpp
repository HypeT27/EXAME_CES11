#include "MenuState.h"

MenuState::MenuState() {

    winclose = new sf::RectangleShape();
    font = new sf::Font();
    menuTexture = new sf::Texture();
    menu = new sf::Sprite();
    menuBackground = new sf::Texture();
    background = new sf::Sprite();

    set_values();
}

MenuState::~MenuState() {
    delete winclose;
    delete font;
    delete menuTexture;
    delete menu;
    delete menuBackground;
    delete background;
}

void MenuState::set_values() {
    menu->setPosition(250,120);
    background->setPosition(0,0);
    background->setScale(1.05,1.05);

    menuTexture->loadFromFile("../src/Images/Menu.png"); //achar textura!!!
    menuBackground->loadFromFile("../src/Images/backgroundmenu.jpg");

    background->setTexture(*menuBackground);
    menu->setTexture(*menuTexture);

}

void MenuState::render(sf::RenderWindow& window) {
    window.draw(*background);
    window.draw(*menu);
}


void MenuState::update(sf::RenderWindow& window) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
    while(window.pollEvent(this->sfEvent))
        if(this->sfEvent.type == sf::Event::Closed)
            window.close();
}

