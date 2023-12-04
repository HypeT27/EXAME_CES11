//
// Created by gabri on 30/11/2023.
//

#include "GameSceneTree.h"


GameSceneTree::GameSceneTree() : root(nullptr){}


GameSceneTree::~GameSceneTree(){}


void GameSceneTree::insert(int posic_x, int posic_y, sf::Texture *texture) {
    root = insertRecursive(root, posic_x, posic_y, texture);
}


GameScene *GameSceneTree::insertRecursive(GameScene *node, int posic_x, int posic_y, sf::Texture *texture) {
    if (node == nullptr) {
        return new GameScene(posic_x, posic_y, texture);
    }

    node->lchild = insertRecursive(node->lchild, posic_x, posic_y, texture);
    node->rchild = insertRecursive(node->rchild, posic_x, posic_y, texture);

    return node;
}


void GameSceneTree::render(sf::RenderTarget& window, int maxLevel) {
    renderBFS(root, window, maxLevel);
}


void GameSceneTree::renderBFS(GameScene* Root, sf::RenderTarget& window, int maxLevel) {
    if (Root == nullptr) {
        return;
    }

    std::queue<std::pair<GameScene*, int>> levelQueue;
    levelQueue.emplace(Root, 0);

    while (!levelQueue.empty()) {
        auto [currentNode, currentLevel] = levelQueue.front();
        levelQueue.pop();

        if (currentLevel <= maxLevel)
            currentNode->render(window);
        else break;

        if (currentNode->lchild != nullptr) {
            levelQueue.push({currentNode->lchild, currentLevel + 1});
        }
        if (currentNode->rchild != nullptr) {
            levelQueue.push({currentNode->rchild, currentLevel + 1});
        }
    }
}


