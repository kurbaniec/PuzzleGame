//
// Created by kurbaniec on 12.01.2022.
//

#ifndef PUZZLE_GAME_PUZZLEGAME_H
#define PUZZLE_GAME_PUZZLEGAME_H


#include "GameBasis.h"
#include "BlockInstance.h"

class PuzzleGame : public GameBasis {
public:
    PuzzleGame(
        GLFWwindow* window,
        const std::shared_ptr<engine::State>& state
    );

    void setup() override;

    void update() override;

private:
    std::shared_ptr<BlockInstance> corner1;
    std::shared_ptr<BlockInstance> corner2;
    std::shared_ptr<BlockInstance> corner3;
    std::shared_ptr<BlockInstance> corner4;

    void processInput(float deltaTime);
};


#endif //PUZZLE_GAME_PUZZLEGAME_H
