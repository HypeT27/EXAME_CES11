#include "Player.h"
#include "playerAttack.h"

void Player::initTextures() {
    this->attackTexture = new sf::Texture;
    this->attackTexture->loadFromFile("../src/Images/playerAttack.png");
}


Player::Player(float x, float y, sf::Texture* texture) {
    this->createSprite(texture);
    this->setPosition(x,y);

    initTextures();

    hitBox.setRadius(19);
    hitBox.setPosition(this->getX(),this->getY());

}


Player::~Player() {
    delete this->attackTexture;
}

void Player::setPosition(float x, float y) {
    if(this->sprite) {
        this->sprite->setPosition(x, y);
    }
}

void Player::Animation(std::vector<playerAttack*>& activeAttacks) {
    if (notMoving && !isAttacking && !isTakingDamage) {
        if(firstTimeMoving){
            rectSourceSprite.left = 228;
            firstTimeMoving = false;
        }
        if (rectSourceSprite.left >= 494)
            rectSourceSprite.left = 228;
        else
            if(cont % 7 == 0)
                rectSourceSprite.left += 38;

        sprite->setTextureRect(rectSourceSprite);
    }

    if (!notMoving && !isAttacking && !isTakingDamage && !isDead) {

            if(firstTimeWalking){
                rectSourceSprite.left = 760;
                firstTimeWalking = false;
            }

            if (rectSourceSprite.left == 950)
                rectSourceSprite.left = 760;
            else
                if(cont % 7 == 0)
                    rectSourceSprite.left += 38;
        sprite->setTextureRect(rectSourceSprite);
    }
    else firstTimeWalking = true;


    if(isAttacking) {
        if(canAttack) {
            auto pAttack = new playerAttack(this->getX(), this->getY(), attackTexture);
            activeAttacks.push_back(pAttack);
            if (firstTimeAttacking) {
                rectSourceSprite.left = 570;
                firstTimeAttacking = false;
            }
            if (rectSourceSprite.left == 684) {
                rectSourceSprite.left = 570;
            } else if (cont % 4 == 0)
                rectSourceSprite.left += 38;
            sprite->setTextureRect(rectSourceSprite);
            canAttack = false;
        }
    }
    else firstTimeAttacking = true;
    cont++;
}

void Player::Dash() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
        if(canDash) {
            sf::Vector2f playerPos = sf::Vector2f(this->getX(), this->getY());
            playerPos = playerPos / std::sqrt(playerPos.x * playerPos.x + playerPos.y * playerPos.y);
            if (isUp)
                this->move(playerPos.x, playerPos.y - 50);
            if (isDown)
                this->move(playerPos.x, playerPos.y + 50);
            if (isRight)
                this->move(playerPos.x + 50, playerPos.y);
            if (isLeft)
                this->move(playerPos.x - 50, playerPos.y);
            canDash = false;
        }
    }
}

void Player::update(sf::Time dt) {
    notMoving = true;
    isLeft = false;
    isRight = false;
    isUp = false;
    isDown = false;
    isAttacking = false;
    if (sf::Keyboard::isKeyPressed((sf::Keyboard::A)) ||
        sf::Keyboard::isKeyPressed((sf::Keyboard::Left))) {
        this->move(-1.f, 0.f);
        isLeft = true;
        notMoving = false;
    }
    if (sf::Keyboard::isKeyPressed((sf::Keyboard::S)) ||
        sf::Keyboard::isKeyPressed((sf::Keyboard::Down))){
        this->move(0.f, 1.f);
        isDown = true;
        notMoving = false;
    }
    if (sf::Keyboard::isKeyPressed((sf::Keyboard::W)) ||
        sf::Keyboard::isKeyPressed((sf::Keyboard::Up))){
        this->move(0.f, -1.f);
        isUp = true;
        notMoving = false;
    }
    if (sf::Keyboard::isKeyPressed((sf::Keyboard::D)) ||
        sf::Keyboard::isKeyPressed((sf::Keyboard::Right))){
        this->move(1.f, 0.f);
        isRight = true;
        notMoving = false;
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        if(canAttack)
            isAttacking = true;

    if(!canDash){
        dashTimer += dt;
        if(dashTimer >= dashCD){
            canDash = true;
            dashTimer = sf::Time::Zero;
        }
    }
    if(!canAttack)
        attackTimer += dt;
        if(attackTimer >= attackCD){
            canAttack = true;
            attackTimer = sf::Time::Zero;
        }
}

bool Player::checkDamage(const Entity* entity) {
    hitBox.setPosition(this->getX(),this->getY());
    auto distance = sqrt(pow(this->getX()-entity->getX(),2)+pow(this->getY()-entity->getY(),2));
    if(distance <= hitBox.getRadius()){
        return true;
    }
    return false;
}

void Player::serialize(FILE* file) const {

    if (this == nullptr) {
        std::cout << "Jogador nulo\n";
        return;
    }

    if (this->sprite == nullptr) {
        std::cout << "Sprite nulo\n";
        return;
    }

    sf::Vector2f position = sprite->getPosition();

    float xValue = position.x;
    float yValue = position.y;

    fprintf(file, "%f\n", xValue);
    fprintf(file, "%f\n", yValue);
}

void Player::deserialize(FILE* file) {
    float xValue;
    float yValue;
    fscanf(file, "%f", &xValue);
    fscanf(file, "%f", &yValue);

    this->setPosition(xValue, yValue);
}



