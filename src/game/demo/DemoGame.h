//
// Created by kurbaniec on 11.01.2022.
//

#ifndef PUZZLE_GAME_DEMOGAME_H
#define PUZZLE_GAME_DEMOGAME_H


#include "../GameBasis.h"
#include "../instances/BlockInstance.h"

class DemoGame : public GameBasis {
public:
    DemoGame(GLFWwindow* window, const std::shared_ptr<engine::State>& state);

    void setup() override;

    void update() override;

private:
    std::shared_ptr<BlockInstance> block1;
    std::shared_ptr<BlockInstance> block2;
    std::shared_ptr<BlockInstance> block3;
    std::shared_ptr<BlockInstance> player;
    std::shared_ptr<BlockInstance> grass;

    void processInput(float deltaTime);
};


#endif //PUZZLE_GAME_DEMOGAME_H
