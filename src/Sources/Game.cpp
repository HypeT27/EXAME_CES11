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
    this->bulletTexture = new sf::Texture;
    this->bulletTexture->loadFromFile("../src/Images/enemyBullet.png");
}

void Game::initEnemies() {
    if(enemiesCounter == 0) {
        enemiesCounter = 2 * level + 3;
    }

    for (int i = 0; i < enemiesCounter; i++) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 10);
        int randomX = dis(gen);
        int randomY = dis(gen);
        aliveEnemies.push_back(new Enemy(200 + 50 * randomX, 100 + 40 * randomY, enemyTexture, this->player));
    }
}

//Constructors/Destructors
Game::Game() : aliveEnemies(), activeBullets(), activeAttacks(){
    this->initTextures();

    this->gameSceneTree = new GameSceneTree();

    this->player = new Player(0,180, playerTexture);

    this->enemy = new Enemy(750, 500, enemyTexture, this->player);

    this->gamescene = new GameScene(0, 0, gamesceneTexture);
    this->estrada = new GameScene(0, 0, estradaTexture);

    this->gameSceneTree->insert(0,0,gamesceneTexture);
    this->gameSceneTree->insert(0,0,estradaTexture);

    this->initEnemies();

}

Game::~Game() {
}


//Functions

void Game::updateDt() {
    dt = dtClock.getElapsedTime();
    dtClock.restart();
}


void Game::update(sf::RenderWindow& window) {
    while(window.pollEvent(this->sfEvent))
        if(this->sfEvent.type == sf::Event::Closed)
            window.close();

    this->player->update(this->dt);
    this->player->Dash();

    for (auto it = activeAttacks.begin(); it != activeAttacks.end();) {
        (*it)->followDirection(window);

        bool eraseIt = false;
        for (auto itEnemy = aliveEnemies.begin(); itEnemy != aliveEnemies.end();) {
            if (*itEnemy != nullptr && (*itEnemy)->checkDamage(*it)) {
                if (*itEnemy != nullptr) {
                    if ((*itEnemy)->hitCount() == 0) {
                        killCounter++;
                        enemiesCounter--;
                        itEnemy = aliveEnemies.erase(itEnemy);
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
            if (aliveEnemy->hitCount() < 1) {
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
            std::cout << "You Lose!!\n";
            window.close();
        }

        if((*it)->getX() > 800 || (*it)->getY() > 600)
            it = activeBullets.erase(it);
        else ++it;
    }

    if(enemiesCounter == 0){
        std::cout << "You won the Level!!\n";
    }
}


void Game::render(sf::RenderWindow& window) {
    this->gameSceneTree->render(window,3);

    this->player->render(window);

    for(auto & aliveEnemy : aliveEnemies){
        if(aliveEnemy != nullptr) {
            (*aliveEnemy).render(window);
        }
    }

    for(auto & activeBullet : activeBullets){
        (*activeBullet).render(window);
    }
    for(auto & activeAttack : activeAttacks){
        (*activeAttack).render(window);
    }

}

int Game::Kills() {
    return killCounter;
}

Player* Game::getPlayer() const {
    return player;
}

std::vector<Enemy*> Game::getEnemies(){
     return aliveEnemies;
}


int Game::getEnemiesCounter() const{
    return enemiesCounter;
}


std::vector<enemyBullet*> Game::getBullets() const {
    return activeBullets;
}

void Game::addBullet() {
    auto pBullet = new enemyBullet(0, 0, bulletTexture, player);
    activeBullets.push_back(pBullet);
}

int Game::getLevel() {
    return level;
}

void Game::changeLevel(int newLevel) {
    this->level = newLevel;
    this->player->setPosition(0,180);
    aliveEnemies.clear();
    activeBullets.clear();
    initEnemies();
}

void Game::changeEnemyCounter(int newEnemyCounter) {
    this->enemiesCounter = newEnemyCounter;
}



