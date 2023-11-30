#ifndef EXAME_CES11_MENUSTATE_H
#define EXAME_CES11_MENUSTATE_H
#include "../Entities/Entity.h"

class MenuState {
    int menuPosic;
    bool pressed, theselect;

    int score;

    sf::RenderWindow* window;
    sf::RectangleShape* winclose;
    sf::Font* font;
    sf::Texture* menuTexture;
    sf::Sprite* menu;

    sf::Vector2i mousePosic;
    sf::Vector2f mouseCoord;

    std::vector<const char*> menuOptions;
    std::vector<sf::Vector2f> wordCoords;
    std::vector<sf::Text> texts;
    std::vector<std::size_t> sizes;

    bool isOnMenu;

protected:
    void set_values();
    void loop_events();
    void render();
    void ranking();

private:

public:
    MenuState();
    ~MenuState();

    void run_menu();
};
#endif //EXAME_CES11_MENUSTATE_H
