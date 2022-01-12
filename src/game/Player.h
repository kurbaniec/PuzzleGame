//
// Created by kurbaniec on 12.01.2022.
//

#ifndef PUZZLE_GAME_PLAYER_H
#define PUZZLE_GAME_PLAYER_H


#include "../engine/instance/instance.h"

class Player : public engine::Instance {
public:
    glm::vec2 input;

    Player(
        std::string id,
        glm::vec3 position,
        glm::vec3 rotation,
        glm::vec3 scale,
        glm::vec3 origin,
        glm::vec3 boundsMin, glm::vec3 boundsMax,
        glm::vec3 gravity = glm::vec3(0, -0.1, 0),
        float slowdown = 0.7f, float movementSpeed = 0.8f, float maxMovementSpeed = 1.8f,
        float rotationSpeed = 90.0f
    );

    void update(float deltaTime);

    void solveCollision(const std::shared_ptr<engine::Instance>& collider);

private:
    glm::vec3 velocity;
    glm::vec3 gravity;
    float slowdown;
    float movementSpeed;
    float maxMovementSpeed;
    float rotationSpeed;
};


#endif //PUZZLE_GAME_PLAYER_H
