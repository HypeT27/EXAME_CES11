#include "MenuState.h"

MenuState::MenuState() {
    window = new sf::RenderWindow();
    winclose = new sf::RectangleShape();
    font = new sf::Font();
    menuTexture = new sf::Texture();
    menu = new sf::Sprite();

    set_values();
}

MenuState::~MenuState() {
    delete window;
    delete winclose;
    delete font;
    delete menuTexture;
    delete menu;
}

void MenuState::set_values() {
    window->create(sf::VideoMode(400,300), "Menu SFML", sf::Style::Titlebar | sf::Style::Close);
    window->setPosition(sf::Vector2i(0,0));

    menuPosic = 0;
    pressed=theselect= false;
    font->loadFromFile("../src/Images/Yellow Style.otf"); //achar fonte!!!
    menuTexture->loadFromFile("../src/Images/Menu.png"); //achar textura!!!

    menu->setTexture(*menuTexture);
}

void MenuState::loop_events() {
    sf::Event event;
    while(window->pollEvent(event)){
        if(event.type == sf::Event::Closed) {
            window->close();
        }
    }
}

void MenuState::render() {
    window->clear();
    window->draw(*menu);
    window->display();
}

void MenuState::ranking() {
    int aux;
    std::vector<int> scoreVector;

    if((int)scoreVector.size() < 6)
        scoreVector.push_back(this->score);
    else
        for(int i=0; i < (int)scoreVector.size(); ++i)
            if(scoreVector[i] < this->score){
                scoreVector[i] = this->score;
                break;
            }

    for (int i=0; i < scoreVector.size(); ++i){
        for (int j=i; j < scoreVector.size(); ++j){
            if (scoreVector[i]>scoreVector[j]){
                aux = scoreVector[i];
                scoreVector[i] = scoreVector[j];
                scoreVector[j] = aux;
            }
        }
    }
}

void MenuState::run_menu() {
    while (window->isOpen()){
        loop_events();
        render();
    }
}

