#include "../Headers/Game.h"

void Game::initTextures(){
    this->playerTexture = new sf::Texture;
    this->playerTexture->loadFromFile("../src/Images/Animations.png");
    this->enemyTexture = new sf::Texture;
    this->enemyTexture->loadFromFile("../src/Images/EnemyShaman.png");
}

void Game::initWindow(){

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
    this->window = new sf::RenderWindow(window_bounds, title);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}


void Game::initStates() {
    this->states.push(new GameState(this->window));
}


//Constructors/Destructors
Game::Game() {
    this->initTextures();
    this->player = new Player(0,0, playerTexture);
    this->enemy = new Enemy(750, 500, enemyTexture, this->player);
    this->initWindow();
    this->initStates();
}

Game::~Game() {
    delete this->window;
    delete this->playerTexture;
    delete this->enemyTexture;

    while(!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}


//Functions

void Game::endApplication() {
    std::cout << "Ending Aplicattion" << "\n";
}

void Game::updateDt() {
    //updates de dt variable with the time it takes to update and render one frame
    this->dt = this->dtClock.getElapsedTime().asSeconds();
}

void Game::updateSFMLEvents() {
    while(this->window->pollEvent(this->sfEvent))
        if(this->sfEvent.type == sf::Event::Closed)
            this->window->close();
}

void Game::update() {
    this->updateSFMLEvents();

    if(!this->states.empty()) {

        if(!this->player->attack())
            this->player->update(this->dt);
        this->enemy->followPlayer(dtClock);
        this->states.top()->updateInput(this->dt);

        this->player->Animation(dtClock);
        this->enemy->Animation(dtClock);


        if (this->states.top()->getQuit()) {
            delete this->states.top();
            this->states.pop();
        }
    }
    else{
        this->endApplication();
        this->window->close();
    }
}

void Game::render() {
    this->window->clear();

    if(!this->states.empty()) {
        this->player->render(this->window);
        this->enemy->render(this->window);
    }

    this->window->display();
}

void Game::run() {
    while(this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}









