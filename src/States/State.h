
#ifndef CMAKESFMLPROJECT_STATE_H
#define CMAKESFMLPROJECT_STATE_H

#include "../Entities/Player.h"


class State {
protected:
    sf::RenderWindow* window;
    std::map<std::string, sf::Texture> textures;
    bool quit;

public:
    State(sf::RenderWindow* window);
    ~State();
    const bool& getQuit() const;

    void checkForQuit();

    void updateInput(sf::Time dt);
    void render(sf::RenderTarget* target = nullptr);
};


#endif //CMAKESFMLPROJECT_STATE_H
