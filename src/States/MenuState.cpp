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

    pressed=theselect= false;
    menuTexture->loadFromFile("../src/Images/Menu.png"); //achar textura!!!
    menuBackground->loadFromFile("../src/Images/backgroundmenu.jpg");
//eu esqueci completamente q existia esse setPositionISSO Q EU FALO Tem um bubble no score eu fiz com
//5 se não me engano e esse ranking daqui de baixo?
//falta alguma coisa ainda como condição pro exame do Verri??
    background->setTexture(*menuBackground);
    menu->setTexture(*menuTexture);

}

void MenuState::render(sf::RenderWindow& window) {
    //window.clear();
    window.draw(*background);
    window.draw(*menu);
    //window.display();
}


void MenuState::loop_events(sf::RenderWindow& window) {
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed) {
            window.close();
        }
    }
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


void MenuState::update(sf::RenderWindow& window) {
    while(window.pollEvent(this->sfEvent))
        if(this->sfEvent.type == sf::Event::Closed)
            window.close();
}

