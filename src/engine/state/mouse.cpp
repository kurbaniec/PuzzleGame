//
// Created by kurbaniec on 14.01.2022.
//

#include "mouse.h"

namespace engine {

    MouseMovement::MouseMovement(
        float screenWidth, float screenHeight, bool firstMouse
    ) : lastX(screenWidth / 2.0f), lastY(screenHeight / 2.0f), xOffset(0), yOffset(0),
        firstMouse(firstMouse) {}
}