//
// Created by kurbaniec on 22.12.2021.
//

#include "instance.h"

#include <utility>
#include "glm/ext/matrix_transform.hpp"

namespace engine {

    Instance::Instance(
        std::string id,
        glm::vec3 position,
        glm::vec3 rotation,
        glm::vec3 scale,
        glm::vec3 origin,
        glm::vec3 boundsMin,
        glm::vec3 boundsMax,
        glm::vec3 localForward,
        glm::vec3 localUp,
        glm::vec3 localRight,
        bool enabled
    ) : id(std::move(id)), position(position), rotation(rotation), scale(scale), origin(origin),
        localForward(glm::vec4(localForward, 1.0f)), forward(glm::vec3{}),
        localUp(glm::vec4(localUp, 1.0f)), up(glm::vec3{}),
        localRight(glm::vec4(localRight, 1.0f)), right(glm::vec3{}),
        enabled(enabled), modelMatrix(glm::mat4(1.0f)),
        boundsVal(Bounds(boundsMin, boundsMax)) {
    }

    void Instance::updateModelMatrix() {
        // Build unique transformation for model
        // See: https://learnopengl.com/Getting-started/
        auto& modelMtx = const_cast<glm::mat4&>(modelMatrix);
        modelMtx = glm::mat4(1.0f);
        auto rotationMtx = glm::mat4(1.0f);
        // Transformations must be in reversed order!
        modelMtx = glm::translate(modelMtx, position);
        modelMtx = glm::translate(modelMtx, -origin);
        rotationMtx = glm::rotate(rotationMtx, glm::radians(rotation.x), glm::vec3(0.1, 0.0, 0.0));
        rotationMtx = glm::rotate(rotationMtx, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
        rotationMtx = glm::rotate(rotationMtx, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));
        modelMtx = modelMatrix * rotationMtx;
        modelMtx = glm::scale(modelMtx, scale);
        modelMtx = glm::translate(modelMtx, origin);
        // Update forward/up/right vectors
        auto& f = const_cast<glm::vec3&>(forward);
        f = rotationMtx * localForward;
        auto& u = const_cast<glm::vec3&>(up);
        u = rotationMtx * localUp;
        auto& r = const_cast<glm::vec3&>(right);
        r = rotationMtx * localRight;
        // Update bounds
        boundsVal.updateWorldBounds(modelMtx);
    }

    const Bounds& Instance::bounds() {
        return boundsVal;
    }

    bool Instance::intersectsAabb(const std::shared_ptr<Instance>& other) const {
        return boundsVal.aabb().intersects(other->boundsVal.aabb());
    }
}

