#include "../Headers/Game.h"

void Game::initTextures(){
    this->playerTexture = new sf::Texture;
    this->playerTexture->loadFromFile("../src/Images/Animations2.png");
    this->enemyTexture = new sf::Texture;
    this->enemyTexture->loadFromFile("../src/Images/EnemyShaman.png");
    this->gamesceneTexture = new sf::Texture;
    this->gamesceneTexture->loadFromFile("../src/Images/scenario.jpg");

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
    this->gamescene = new GameScene(0, 0, gamesceneTexture);


    for (int i =0; i<10; i++) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 10);
        int randomX = dis(gen);
        int randomY = dis(gen);
        aliveEnemies.push_back(new Enemy(200+30*randomX, 100+20*randomY, enemyTexture, this->player));
    }



    this->initWindow();

    this->initStates();
}

Game::~Game() {
    delete this->window;
    delete this->playerTexture;
    delete this->enemyTexture;
    delete this->gamesceneTexture;

    delete this->player;

    for(auto bullet : activeBullets)
        delete bullet;

    for(auto attack : activeAttacks)
        delete attack;

    for(auto enemies: aliveEnemies)
        delete enemies;


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
    dt = dtClock.getElapsedTime();
    dtClock.restart();
}

void Game::updateSFMLEvents() {
    while(this->window->pollEvent(this->sfEvent))
        if(this->sfEvent.type == sf::Event::Closed)
            this->window->close();
}

void Game::update() {
    this->updateSFMLEvents();

    if(!this->states.empty()) {

        this->player->update(this->dt);
        this->player->Dash();

        for (auto it = activeAttacks.begin(); it != activeAttacks.end();) {
            (*it)->followDirection(this->window);

            bool eraseIt = false;
            for (auto itEnemy = aliveEnemies.begin(); itEnemy != aliveEnemies.end();) {
                if (*itEnemy != nullptr && (*itEnemy)->checkDamage(*it)) {
                    if (*itEnemy != nullptr) {
                        if ((*itEnemy)->hitCount() == 4) {
                            enemiesCounter--;
                            itEnemy = aliveEnemies.erase(itEnemy);
                            delete *itEnemy;
                            eraseIt = true;
                        }
                        else {
                            (*itEnemy)->hitCountAdd();
                            eraseIt = true;
                        }
                    }
                    break;
                }
                else ++itEnemy;
            }
            if ((*it)->getX() > 800 || (*it)->getY() > 600)
                eraseIt = true;

            if (eraseIt)
                it = activeAttacks.erase(it);
            else ++it;

        }

        for(auto & aliveEnemy : aliveEnemies) {
            if(aliveEnemy != nullptr) {
                if (aliveEnemy->hitCount() < 5) {
                    (*aliveEnemy).Animation(dtClock);
                    (*aliveEnemy).attack(activeBullets);
                    (*aliveEnemy).followPlayer();
                }
            }
        }

        this->player->Animation(activeAttacks);

        for(auto it = activeBullets.begin(); it != activeBullets.end();) {
            (*it)->followDirection();
            (*it)->Animation();
            if(this->player->checkDamage(*it)) {
                it = activeBullets.erase(it);
                std::cout << "You Lose!!";
                this->window->close();
            }

            if((*it)->getX() > 800 || (*it)->getY() > 600)
                it = activeBullets.erase(it);
            else ++it;
        }

        if(enemiesCounter == 0){
            std::cout << "You won!!";
            this->window->close();

        }


        this->states.top()->updateInput(this->dt);

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
        this->gamescene->render(this->window);
        this->player->render(this->window);

        for(auto & aliveEnemy : aliveEnemies){
            if(aliveEnemy != nullptr) {
                (*aliveEnemy).render(this->window);

            }
        }

        for(auto & activeBullet : activeBullets){
            (*activeBullet).render(this->window);
        }
        for(auto & activeAttack : activeAttacks){
            (*activeAttack).render(this->window);
        }

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









