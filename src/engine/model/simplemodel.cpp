//
// Created by kurbaniec on 21.12.2021.
//

#include <string>
#include "simplemodel.h"

namespace engine {

    SimpleModel::SimpleModel(
            const std::string& path,
            std::shared_ptr<Shader> shader,
            bool transparent,
            std::function<std::shared_ptr<Instance>
                    (std::string, glm::vec3, glm::vec3, glm::vec3, glm::vec3)> creator
    ) : Model(std::move(shader), transparent, std::move(creator)) {
        loadModel(path, textures_loaded, meshes);
    }

    void SimpleModel::draw() {
        //shader->use();
        for (auto& mesh: meshes)
            mesh.Draw(shader);
    }

    glm::mat4 SimpleModel::getModelMatrix() {
        // Build unique transformation for model
        // See: https://learnopengl.com/Getting-started/
        modelMatrix = glm::mat4(1.0f);
        // Transformations must be in reversed order!
        return glm::mat4();
    }

    std::shared_ptr<Instance>
    SimpleModel::create(std::string id, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 origin) {
        return std::shared_ptr<Instance>();
    }

}
