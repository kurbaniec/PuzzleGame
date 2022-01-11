//
// Created by kurbaniec on 11.01.2022.
//

#ifndef PUZZLE_GAME_GAMEBASIS_H
#define PUZZLE_GAME_GAMEBASIS_H

#include <memory>
#include "../engine/state/state.h"
#include "GLFW/glfw3.h"

class GameBasis {
public:
    GameBasis(
        GLFWwindow* window,
        std::shared_ptr<engine::State> state
    ) : window(window), state(std::move(state)) {}

    virtual void setup() = 0;

    virtual void update() = 0;

protected:
    GLFWwindow* window;
    std::shared_ptr<engine::State> state;
};

#endif //PUZZLE_GAME_GAMEBASIS_H
