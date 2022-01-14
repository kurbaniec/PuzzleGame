//
// Created by kurbaniec on 23.12.2021.
//

#include "window.h"
#include "glm/trigonometric.hpp"
#include "glm/ext/matrix_clip_space.hpp"

namespace engine {

    Window::Window(
        int width, int height, const std::shared_ptr<State>& state
    ) : width(width), height(height), initialWidth(width), initialHeight(height), state(state) {

    }

    glm::mat4 Window::getProjectionMatrix() {
        return glm::perspective(
            glm::radians(state.lock()->getCamera()->getZoom()),
            (float) width / (float) height, 0.1f, 200.0f
        );
    }
}