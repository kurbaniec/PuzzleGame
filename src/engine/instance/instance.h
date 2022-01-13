//
// Created by kurbaniec on 22.12.2021.
//

#ifndef PUZZLE_GAME_ENGINE_INSTANCE_H
#define PUZZLE_GAME_ENGINE_INSTANCE_H

#include <string>
#include <glm/glm.hpp>
#include <memory>
#include "../collision/boundingbox.h"
//#include "../model/model.h"
#include <set>

namespace engine {
    class Model;

    class Instance {
    public:
        const std::string id;
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        glm::vec3 origin;
        const glm::mat4 modelMatrix;
        glm::vec4 localForward;
        glm::vec4 localUp;
        glm::vec4 localRight;
        const glm::vec3 forward;
        const glm::vec3 up;
        const glm::vec3 right;
        bool enabled;
        std::set<std::string> tags;

        Instance(
            std::string id,
            glm::vec3 position,
            glm::vec3 rotation,
            glm::vec3 scale,
            glm::vec3 origin,
            glm::vec3 boundsMin,
            glm::vec3 boundsMax,
            std::set<std::string> tags = {},
            bool enabled = true,
            glm::vec3 localForward = glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3 localUp = glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3 localRight = glm::vec3(1.0f, 0.0f, 0.0f)
        );

        const Bounds& bounds();
        virtual bool intersectsAabb(const std::shared_ptr<Instance>& other) const;
        virtual void updateModelMatrix();

    protected:
        Bounds boundsVal;
        //std::weak_ptr<Model> model;
    };
}

#endif //PUZZLE_GAME_ENGINE_INSTANCE_H
