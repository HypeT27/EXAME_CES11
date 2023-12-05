//
// Created by gabri on 30/11/2023.
//

#ifndef EXAME_CES11_GAMESCENETREE_H
#define EXAME_CES11_GAMESCENETREE_H
#include "GameScene.h"
#include <queue>


class GameSceneTree {
public:

    GameSceneTree();
    ~GameSceneTree();

    void insert(int posic_x, int posic_y, sf::Texture* texture);

    static void renderBFS(GameScene* Root, sf::RenderTarget& window, int maxLevel);

    void render(sf::RenderTarget& window, int maxLevel);

private:
    GameScene* root;

    GameScene* insertRecursive(GameScene* node, int posic_x, int posic_y, sf::Texture* texture);
};


#endif //EXAME_CES11_GAMESCENETREE_H
