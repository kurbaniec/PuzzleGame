//
// Created by kurbaniec on 22.12.2021.
//

#ifndef PUZZLE_GAME_ENGINE_INSTANCE_H
#define PUZZLE_GAME_ENGINE_INSTANCE_H

#include <string>
#include <glm/glm.hpp>
#include "../model/model.h"

namespace engine {
    class Model;

    class Instance {
    public:
        const std::string id;
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        glm::vec3 origin;
        glm::mat4 modelMatrix;
        bool enabled = true;

        Instance(
            std::string id,
            glm::vec3 position,
            glm::vec3 rotation,
            glm::vec3 scale,
            glm::vec3 origin
        );

        virtual glm::mat4& updateModelMatrix();

    protected:
        std::weak_ptr<Model> model;
    };
}

#endif //PUZZLE_GAME_ENGINE_INSTANCE_H
