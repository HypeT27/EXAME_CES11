#ifndef EXAME_CES11_MENUSTATE_H
#define EXAME_CES11_MENUSTATE_H
#include "../Entities/Entity.h"

class MenuState {
private:
    sf::Event sfEvent;
    sf::Texture* menuTexture;
    sf::Sprite* menu;
    sf::Texture* menuBackground;
    sf::Sprite* background;

    std::vector<const char*> menuOptions;
    std::vector<sf::Vector2f> wordCoords;
    std::vector<sf::Text> texts;
    std::vector<std::size_t> sizes;

protected:
    void set_values();

public:
    MenuState();
    ~MenuState();
    void render(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
};
#endif //EXAME_CES11_MENUSTATE_H
