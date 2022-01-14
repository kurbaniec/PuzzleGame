//
// Created by kurbaniec on 14.01.2022.
//

#ifndef PUZZLE_GAME_ENEMY_H
#define PUZZLE_GAME_ENEMY_H

#include "../../engine/instance/instance.h"

class Enemy : public engine::Instance {
public:
    Enemy(
        std::string id,
        glm::vec3 position,
        glm::vec3 rotation,
        glm::vec3 scale,
        glm::vec3 origin,
        glm::vec3 boundsMin, glm::vec3 boundsMax,
        glm::vec3 startPosition = glm::vec3(0, 0, 0),
        glm::vec3 endPosition = glm::vec3(0, 4, 0),
        float movementSpeed = 1.1f,
        float rotationSpeed = 110.0f
    );

    void update(float deltaTime);

    void setStartPosition(glm::vec3 position);
    void setEndPosition(glm::vec3 position);
    void setRotationSpeed(float rotation);

private:
    glm::vec3 startPostion;
    glm::vec3 endPosition;
    float movementSpeed;
    float rotationSpeed;
};


#endif //PUZZLE_GAME_ENEMY_H
