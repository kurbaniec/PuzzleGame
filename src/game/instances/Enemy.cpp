//
// Created by kurbaniec on 14.01.2022.
//

#include "Enemy.h"

Enemy::Enemy(
    std::string id,
    glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 origin,
    glm::vec3 boundsMin, glm::vec3 boundsMax,
    glm::vec3 startPosition,
    glm::vec3 endPosition,
    float movementSpeed,
    float rotationSpeed
) : Instance(std::move(id), startPosition, rotation, scale, origin, boundsMin, boundsMax),
    startPostion(startPosition), endPosition(endPosition),
    movementSpeed(movementSpeed), rotationSpeed(rotationSpeed) {
}

void Enemy::update(float deltaTime) {
    // For now supports only check on y axis
    if (position.y > endPosition.y || position.y < startPostion.y) {
        movementSpeed *= -1;
    }
    position += up * movementSpeed * deltaTime;
    rotation.y = std::fmod(rotation.y + (rotationSpeed * deltaTime), 360.0f);
    updateModelMatrix();
}

void Enemy::setStartPosition(glm::vec3 position) {
    startPostion = position;
}

void Enemy::setEndPosition(glm::vec3 position) {
    endPosition = position;
}

void Enemy::setRotationSpeed(float rotation) {
    rotationSpeed = rotation;
}
