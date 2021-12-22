//
// Created by kurbaniec on 22.12.2021.
//

#include "instance.h"
#include "glm/ext/matrix_transform.hpp"

namespace engine {

    glm::mat4 Instance::getModelMatrix() {
        // Build unique transformation for model
        // See: https://learnopengl.com/Getting-started/
        modelMatrix = glm::mat4(1.0f);
        // Transformations must be in reversed order!
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(0.1, 0.0, 0.0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));
        modelMatrix = glm::scale(modelMatrix, scale);
        modelMatrix = glm::translate(modelMatrix, origin);
        return modelMatrix;
    }
}

