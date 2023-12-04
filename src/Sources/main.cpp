
#include "../Headers/ScreenHandler.h"
#include "../Save/GameData.h"

int main()
{
    sf::RenderWindow window;

    std::ifstream ifs("Config/window.ini");
    std::string title = "None";
    sf::VideoMode window_bounds(800,600);
    unsigned framerate_limit = 60;
    bool vertical_sync_enabled = false;

    if(ifs.is_open()){
        std::getline(ifs,title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
    }
    window.create(window_bounds,title);
    window.setFramerateLimit(framerate_limit);
    window.setVerticalSyncEnabled(vertical_sync_enabled);

    ScreenHandler screenhandler;

    while(window.isOpen()) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            window.close();
        window.clear();
        screenhandler.update(window);
        screenhandler.render(window);
        window.display();
    }

    return 0;
}