#ifndef EXAME_CES11_MENUSTATE_H
#define EXAME_CES11_MENUSTATE_H
#include "../Entities/Entity.h"

class MenuState {
private:
    bool pressed, theselect;

    sf::RectangleShape* winclose;
    sf::Font* font;
    sf::Event sfEvent;
    sf::Texture* menuTexture;
    sf::Sprite* menu;
    sf::Texture* menuBackground;
    sf::Sprite* background;

    sf::Vector2i mousePosic;
    sf::Vector2f mouseCoord;

    std::vector<const char*> menuOptions;
    std::vector<sf::Vector2f> wordCoords;
    std::vector<sf::Text> texts;
    std::vector<std::size_t> sizes;


protected:
    void set_values();
    void loop_events(sf::RenderWindow& window);

private:

public:
    MenuState();
    ~MenuState();
    void render(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
};
#endif //EXAME_CES11_MENUSTATE_H
