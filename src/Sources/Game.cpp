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
    this->bulletTexture = new sf::Texture;
    this->bulletTexture->loadFromFile("../src/Images/enemyBullet.png");
}

//Constructors/Destructors
Game::Game() : aliveEnemies(), activeBullets(), activeAttacks(){
    this->initTextures();

    this->gameSceneTree = new GameSceneTree();

    this->player = new Player(0,180, playerTexture);

    this->player = new Player(20,300, playerTexture);
    this->enemy = new Enemy(750, 500, enemyTexture, this->player);
    this->player = new Player(0,0, playerTexture);

    this->gamescene = new GameScene(0, 0, gamesceneTexture);
    this->estrada = new GameScene(0, 0, estradaTexture);
    this->lake = new GameScene (-20, -380, lakeTexture);
    this->tree1 = new GameScene(20, 0, tree1Texture);
    this->tree2 = new GameScene(-540, -420, tree2Texture);
    this->tree3 = new GameScene(-670, -250, tree3Texture);
    this->tree4 = new GameScene(-340, -80, tree4Texture);
    this->cactus = new GameScene(-525, -145, cactusTexture);
    this->stone = new GameScene(-690, -20, stoneTexture);

    this->gameSceneTree->insert(0,0,gamesceneTexture);
    this->gameSceneTree->insert(0,0,estradaTexture);
    this->gameSceneTree->insert(-20,-380,lakeTexture);
    this->gameSceneTree->insert(20,0,tree1Texture);
    this->gameSceneTree->insert(-540,-420,tree2Texture);
    this->gameSceneTree->insert(-670,-250,tree3Texture);
    this->gameSceneTree->insert(-340,-80,tree4Texture);
    this->gameSceneTree->insert(-525,-145,cactusTexture);
    this->gameSceneTree->insert(-690,-20,stoneTexture);


    enemiesCounter = 6;

    for (int i =0; i<enemiesCounter; i++) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 10);
        int randomX = dis(gen);
        int randomY = dis(gen);
        aliveEnemies.push_back(new Enemy(200+50*randomX, 100+40*randomY, enemyTexture, this->player));
    }

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
                    if ((*itEnemy)->hitCount() == 4) {
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
            window.close();
        }

        if((*it)->getX() > 800 || (*it)->getY() > 600)
            it = activeBullets.erase(it);
        else ++it;
    }

    if(enemiesCounter == 0){
        std::cout << "You won!!";
        window.close();

    }
}


void Game::render(sf::RenderWindow& window) {
    this->gameSceneTree->render(window,10);

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

std::vector<enemyBullet*> Game::getBullets() const {
    return activeBullets;
}

void Game::addBullet() {
    auto pBullet = new enemyBullet(0, 0, bulletTexture, player);
    activeBullets.push_back(pBullet);
}

