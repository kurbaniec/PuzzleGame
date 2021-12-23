//
// Created by kurbaniec on 23.12.2021.
//

#ifndef PUZZLE_GAME_ENGINE_WINDOW_H
#define PUZZLE_GAME_ENGINE_WINDOW_H

#include <memory>
#include "../state/state.h"

namespace engine {
    class State;

    class Window {
    public:
        int width;
        int height;

        Window(int width, int height, const std::shared_ptr<State>& state);

        virtual glm::mat4 getProjectionMatrix();

    private:
        std::weak_ptr<State> state;
        const int initialWidth;
        const int initialHeight;
    };
}



#endif //PUZZLE_GAME_ENGINE_WINDOW_H
