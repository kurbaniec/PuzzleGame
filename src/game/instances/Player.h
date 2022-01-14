//
// Created by kurbaniec on 12.01.2022.
//

#ifndef PUZZLE_GAME_PLAYER_H
#define PUZZLE_GAME_PLAYER_H


#include "../../engine/instance/instance.h"

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
        glm::vec3 gravity = glm::vec3(0, -4, 0),
        float slowdown = 0.9f, float movementSpeed = 1.1f, float maxMovementSpeed = 2.4f,
        float rotationSpeed = 110.0f, glm::vec3 resetPosition = glm::vec3(5.5f, 0.4f, 5.5f)
    );

    void update(float deltaTime);

    void solveCollision(const std::shared_ptr<engine::Instance>& collider);

    void reset();

private:
    glm::vec3 velocity;
    glm::vec3 gravity;
    float slowdown;
    float movementSpeed;
    float maxMovementSpeed;
    float rotationSpeed;
    glm::vec3 resetPostion;
};


#endif //PUZZLE_GAME_PLAYER_H
