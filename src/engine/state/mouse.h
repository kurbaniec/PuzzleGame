//
// Created by kurbaniec on 14.01.2022.
//

#ifndef PUZZLE_GAME_ENGINE_MOUSE_H
#define PUZZLE_GAME_ENGINE_MOUSE_H

namespace engine {
    class MouseMovement {
    public:
        float lastX;
        float lastY;
        float xOffset;
        float yOffset;
        bool firstMouse;

        MouseMovement(float screenWidth, float screenHeight, bool firstMouse = false);
    };
}


#endif //PUZZLE_GAME_ENGINE_MOUSE_H
