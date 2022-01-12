//
// Created by kurbaniec on 06.01.2022.
//

#include "boundingbox.h"
#include "glm/gtx/string_cast.hpp"

namespace engine {

    BoundingBox::BoundingBox(glm::vec3& min, glm::vec3& max)
        : minVal(min), maxVal(max) {}

    const glm::vec3& BoundingBox::min() const {
        return minVal;
    }

    const glm::vec3& BoundingBox::max() const {
        return maxVal;
    }

    float BoundingBox::height() const {
        return glm::length(maxVal.y - minVal.y);
    }

    float BoundingBox::width() const {
        return glm::length(maxVal.x - minVal.x);
    }

    float BoundingBox::depth() const {
        return glm::length(maxVal.z - minVal.z);
    }

    void BoundingBox::updateWorld(const glm::vec3& localMin, const glm::vec3& localMax, glm::mat4 modelMatrix) {
        minVal = glm::vec3(modelMatrix * glm::vec4(localMin, 1.0f));
        maxVal = glm::vec3(modelMatrix * glm::vec4(localMax, 1.0f));
    }

    void BoundingBox::updateWorldAabb(const glm::vec3& localMin, const glm::vec3& localMax, glm::mat4 modelMatrix) {
        glm::vec3 points[8] = {
            glm::vec3(modelMatrix * glm::vec4(localMin, 1.0f)),
            glm::vec3(modelMatrix * glm::vec4(localMin.x, localMin.y, localMax.z, 1.0f)),
            glm::vec3(modelMatrix * glm::vec4(localMax.x, localMin.y, localMin.z, 1.0f)),
            glm::vec3(modelMatrix * glm::vec4(localMax.x, localMin.y, localMax.z, 1.0f)),
            glm::vec3(modelMatrix * glm::vec4(localMax, 1.0f)),
            glm::vec3(modelMatrix * glm::vec4(localMax.x, localMax.y, localMin.z, 1.0f)),
            glm::vec3(modelMatrix * glm::vec4(localMin.x, localMax.y, localMax.z, 1.0f)),
            glm::vec3(modelMatrix * glm::vec4(localMin.x, localMax.y, localMin.z, 1.0f)),
        };
        // Assign random points from calculated ones
        // Note: Do not assign default values like vec3(0.0f)
        // Why? Min values can be greater than 0!
        glm::vec3 min = points[0];
        glm::vec3 max = points[0];
        for (auto& point: points) {
            if (point.x < min.x) min.x = point.x;
            if (point.y < min.y) min.y = point.y;
            if (point.z < min.z) min.z = point.z;
            if (point.x > max.x) max.x = point.x;
            if (point.y > max.y) max.y = point.y;
            if (point.z > max.z) max.z = point.z;
        }
        minVal = min;
        maxVal = max;
    }

    bool BoundingBox::intersects(const BoundingBox& other) const {
        // See: https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
        // And: https://stackoverflow.com/a/46682296/12347616
        return (minVal.x < other.maxVal.x && maxVal.x > other.minVal.x) &&
               (minVal.y < other.maxVal.y && maxVal.y > other.minVal.y) &&
               (minVal.z < other.maxVal.z && maxVal.z > other.minVal.z);
    }

    std::ostream& operator<<(std::ostream& os, const BoundingBox& box) {
        os << "{ min: " << glm::to_string(box.minVal) << ", max: " << glm::to_string(box.maxVal) << " }";
        return os;
    }

    Bounds::Bounds(glm::vec3 min, glm::vec3 max)
        : localBb(BoundingBox(min, max)),
          worldBb(BoundingBox(min, max)),
          worldAabb(BoundingBox(min, max)) {}

    const BoundingBox& Bounds::local() const {
        return localBb;
    }

    const BoundingBox& Bounds::world() const {
        return worldBb;
    }

    const BoundingBox& Bounds::aabb() const {
        return worldAabb;
    }

    void Bounds::setLocalBounds(glm::vec3 newMin, glm::vec3 newMax) {
        localBb.minVal = newMin;
        localBb.maxVal = newMax;
    }

    void Bounds::updateWorldBounds(glm::mat4 modelMatrix) {
        worldBb.updateWorld(localBb.minVal, localBb.maxVal, modelMatrix);
        worldAabb.updateWorldAabb(localBb.minVal, localBb.maxVal, modelMatrix);
    }

    std::ostream& operator<<(std::ostream& os, const Bounds& bounds) {
        os << "{ " << std::endl <<
           "\tlocal: " << bounds.localBb << ", " << std::endl <<
           "\tworld: " << bounds.worldBb << ", " << std::endl <<
           "\taabb: " << bounds.worldAabb << std::endl <<
           "}";
        return os;
    }
}