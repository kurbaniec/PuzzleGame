//
// Created by kurbaniec on 12.01.2022.
//

#include <iostream>
#include "Player.h"

Player::Player(
    std::string id,
    glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 origin,
    glm::vec3 boundsMin, glm::vec3 boundsMax,
    glm::vec3 gravity, float slowdown, float movementSpeed, float maxMovementSpeed, float rotationSpeed
) : Instance(std::move(id), position, rotation, scale, origin, boundsMin, boundsMax),
    gravity(gravity), velocity(0), slowdown(slowdown),
    movementSpeed(movementSpeed), maxMovementSpeed(maxMovementSpeed),
    rotationSpeed(rotationSpeed), input(glm::vec2(0.0f)) {

}

void Player::update(float deltaTime) {
    // See: https://www.youtube.com/watch?v=c4b9lCfSDQM
    auto inputForward = input.x;
    auto inputAngle = input.y;

    if (inputForward != 0) {
        // velocity.z = std::max(velocity.z * inputForward * speed, maxSpeed);
        velocity.z += inputForward * movementSpeed;
        if (velocity.z > 0) {
            velocity.z = std::min(velocity.z, maxMovementSpeed);
        } else {
            velocity.z = std::max(velocity.z, -maxMovementSpeed);
        }
    } else {
        if (velocity.z > 0) {
            velocity.z = std::max(velocity.z - slowdown, 0.0f);
        } else {
            velocity.z = std::min(velocity.z + slowdown, 0.0f);
        }
    }

    position += forward * velocity.z * deltaTime;
    position += up * velocity.y * deltaTime;

    if (inputAngle != 0) {
        rotation.y = std::fmod(rotation.y + (inputAngle * rotationSpeed * deltaTime), 360.0f);
    }

    velocity.y += gravity.y * deltaTime;
}

void Player::solveCollision(const std::shared_ptr<engine::Instance>& collider) {
    auto playerMin = this->bounds().aabb().min();
    auto colliderMax = collider->bounds().aabb().max();

    auto playerHeight = this->bounds().aabb().height();
    auto otherHeight = collider->bounds().aabb().height();

    // std::cout << position.y << " " << collider->position.y << std::endl;
    auto kek = (colliderMax.y-playerMin.y);

    if (playerMin.y < colliderMax.y && (colliderMax.y-playerMin.y) < playerHeight/2) {
        velocity.y = 0;
        position.y = colliderMax.y;
    }
}
