//
// Created by kurbaniec on 22.12.2021.
//

#include "model.h"

#include <utility>

namespace engine {
    std::shared_ptr<Instance>
    engine::Model::create(std::string id, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 origin) {
        return creator(std::move(id), position, rotation, scale, origin);
    }

    Model::Model(
        std::string id,
        std::shared_ptr<Shader> shader,
        std::function<std::shared_ptr<Instance>
            (std::string, glm::vec3, glm::vec3, glm::vec3, glm::vec3)> creator
    ) : id(std::move(id)), shader(std::move(shader)), creator(std::move(creator)) {}

}
