//
// Created by kurbaniec on 12.01.2022.
//

#ifndef PUZZLE_GAME_PUZZLEGAME_H
#define PUZZLE_GAME_PUZZLEGAME_H


#include "GameBasis.h"
#include "instances/BlockInstance.h"
#include "../engine/factory/InstanceFactory.h"
#include "instances/Player.h"
#include "instances/Enemy.h"
#include <set>

class PuzzleGame : public GameBasis {
public:
    friend class PuzzleGameLevel;

    PuzzleGame(
        GLFWwindow* window,
        const std::shared_ptr<engine::State>& state
    );

    void setup() override;

    void update() override;

private:
    std::shared_ptr<engine::Camera> camera;
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<engine::Instance>> blocks;
    std::vector<std::shared_ptr<engine::Instance>> stars;
    int starsCollected = 0;

    void processInput(float deltaTime);

    void reset();

    static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
};


#endif //PUZZLE_GAME_PUZZLEGAME_H
