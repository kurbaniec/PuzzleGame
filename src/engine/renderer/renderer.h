//
// Created by kurbaniec on 23.12.2021.
//

#ifndef PUZZLE_GAME_ENGINE_RENDERER_H
#define PUZZLE_GAME_ENGINE_RENDERER_H

#include <memory>
#include "../state/state.h"
#include "../model/triangle.h"

namespace engine {
    class Renderer {
    public:
        explicit Renderer(std::shared_ptr<State> state);

        void setup();

        void clear();

        void draw();

    private:
        std::shared_ptr<State> state;
        std::vector<std::reference_wrapper<Triangle>> transparentTriangles;
    };
}

#endif //PUZZLE_GAME_ENGINE_RENDERER_H
