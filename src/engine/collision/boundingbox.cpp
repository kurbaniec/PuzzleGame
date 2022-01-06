//
// Created by kurbaniec on 06.01.2022.
//

#include "boundingbox.h"

namespace engine {

    BoundingBox::BoundingBox(glm::vec3& min, glm::vec3& max)
        : localMin(min), localMax(max), valMin(min), valMax(max) {}

    const glm::vec3& BoundingBox::min() const {
        return valMin;
    }

    const glm::vec3& BoundingBox::max() const {
        return valMax;
    }

    float BoundingBox::height() const {
        return glm::length(valMax.y - valMin.y);
    }

    float BoundingBox::width() const {
        return glm::length(valMax.x - valMin.x);
    }

    float BoundingBox::depth() const {
        return glm::length(valMax.z - valMin.z);
    }

    void BoundingBox::update(glm::mat4 modelMatrix) {
        valMin = glm::vec3(modelMatrix * glm::vec4(localMin, 1.0f));
        valMax = glm::vec3(modelMatrix * glm::vec4(localMax, 1.0f));
    }

    Bounds::Bounds(glm::vec3 min, glm::vec3 max)
        : min(min), max(max),
          localBb(BoundingBox(this->min, this->max)),
          worldBb(BoundingBox(this->min, this->max)) {}

    const BoundingBox& Bounds::local() const {
        return localBb;
    }

    const BoundingBox& Bounds::world() const {
        return worldBb;
    }

    void Bounds::setLocalBounds(glm::vec3 newMin, glm::vec3 newMax) {
        min.x = newMin.x;
        min.y = newMin.y;
        min.z = newMin.z;
        max.x = newMax.x;
        max.y = newMax.y;
        max.z = newMax.z;
    }

    void Bounds::updateWorldBounds(glm::mat4 modelMatrix) {
        worldBb.update(modelMatrix);
    }
}