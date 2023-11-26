#ifndef EXAME_CES11_MENUSTATE_H
#define EXAME_CES11_MENUSTATE_H
#include "../Entities/Entity.h"

class MenuState {
private:
    void initKeybinds();

public:
    MenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
    ~MenuState();


    //Functions
    void render(sf::RenderTarget* target = nullptr);
};


#endif //EXAME_CES11_MENUSTATE_H
