#include "../Headers/Game.h"

void Game::initTextures(){
    this->playerTexture = new sf::Texture;
    this->playerTexture->loadFromFile("../src/Images/Animations2.png");
    this->enemyTexture = new sf::Texture;
    this->enemyTexture->loadFromFile("../src/Images/EnemyShaman.png");
    this->gamesceneTexture = new sf::Texture;
    this->gamesceneTexture->loadFromFile("../src/Images/scenario.jpg");
    this->estradaTexture = new sf::Texture;
    this->estradaTexture->loadFromFile("../src/Images/Estrada.png");
    this->lakeTexture = new sf::Texture;
    this->lakeTexture->loadFromFile ("../src/Images/Lake.png");
    this->tree1Texture = new sf::Texture;
    this->tree1Texture->loadFromFile("../src/Images/Tree1.png");
    this->tree2Texture = new sf::Texture;
    this->tree2Texture->loadFromFile("../src/Images/Tree2.png");
    this->tree3Texture = new sf::Texture;
    this->tree3Texture->loadFromFile("../src/Images/Tree3.png");
    this->tree4Texture = new sf::Texture;
    this->tree4Texture->loadFromFile("../src/Images/Tree4.png");
    this->cactusTexture = new sf::Texture;
    this->cactusTexture->loadFromFile("../src/Images/Cactus.png");
    this->stoneTexture = new sf::Texture;
    this->stoneTexture->loadFromFile("../src/Images/Stone.png");



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
    this->player = new Player(20,300, playerTexture);
    this->enemy = new Enemy(750, 500, enemyTexture, this->player);
    this->gamescene = new GameScene(0, 0, gamesceneTexture);
    this->estrada = new GameScene(0, 0, estradaTexture);
    this->lake = new GameScene (-20, -380, lakeTexture);
    this->tree1 = new GameScene(20, 0, tree1Texture);
    this->tree2 = new GameScene(-540, -420, tree2Texture);
    this->tree3 = new GameScene(-670, -250, tree3Texture);
    this->tree4 = new GameScene(-340, -80, tree4Texture);
    this->cactus = new GameScene(-525, -145, cactusTexture);
    this->stone = new GameScene(-690, -20, stoneTexture);



    this->enemy = new Enemy(300, 300, enemyTexture, this->player);
    this->initWindow();

    this->initStates();
}

Game::~Game() {
    delete this->window;
    delete this->playerTexture;
    delete this->enemyTexture;
    delete this->gamesceneTexture;
    delete this->estradaTexture;
    delete this->lakeTexture;
    delete this->tree1Texture;
    delete this->tree2Texture;
    delete this->tree3Texture;
    delete this->tree4Texture;
    delete this->cactusTexture;
    delete this->stoneTexture;



    delete this->player;
    delete this->enemy;
    gamescene->~GameScene();
    estrada->~GameScene();
    lake->~GameScene();
    tree1->~GameScene();
    tree2->~GameScene();
    tree3->~GameScene();
    tree4->~GameScene();
    cactus->~GameScene();
    stone->~GameScene();


    for(auto bullet : activeBullets)
        delete bullet;

    for(auto attack : activeAttacks)
        delete attack;


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
        this->enemy->followPlayer();
        this->player->Animation(activeAttacks);
        this->enemy->Animation(dtClock);
        this->enemy->attack(activeBullets);

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

        for(auto it = activeAttacks.begin(); it != activeAttacks.end();) {
            (*it)->followDirection(this->window);
            if(this->enemy->checkDamage(*it)) {
                hitCounter++;
                if(hitCounter == 5) {
                    std::cout << "You Won!!";
                    this->window->close();
                }
                it = activeAttacks.erase(it);
                break;
            }
            if((*it)->getX() > 800 || (*it)->getY() > 600)
                it = activeAttacks.erase(it);
            else ++it;
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
        this->estrada->render(this->window);
        this->lake->render(this->window);
        this->tree1->render(this->window);
        this->tree2->render(this->window);
        this->tree3->render(this->window);
        this->tree4->render(this->window);
        this->cactus->render(this->window);
        this->stone->render(this->window);
        this->player->render(this->window);
        this->enemy->render(this->window);


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









