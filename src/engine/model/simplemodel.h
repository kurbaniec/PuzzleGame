//
// Created by kurbaniec on 21.12.2021.
//

#ifndef PUZZLE_GAME_ENGINE_SIMPLEMODEL_H
#define PUZZLE_GAME_ENGINE_SIMPLEMODEL_H

#ifndef PUZZLE_GAME_ENGINE_MODEL_H
#include "model.h"
#endif //PUZZLE_GAME_ENGINE_MODEL_H

namespace engine {

    class SimpleModel : public Model {
    public:
        // model data
        std::vector<Texture> textures_loaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        std::vector<Mesh> meshes;
        std::string directory;

        std::vector<std::shared_ptr<Instance>> instances;

        // constructor, expects a filepath to a 3D model.
        explicit SimpleModel(
            const std::string& id,
            const std::string& path,
            std::shared_ptr<Shader> shader,
            std::function<std::shared_ptr<Instance>
                (std::string, glm::vec3, glm::vec3, glm::vec3, glm::vec3)> creator
        );

        void draw(glm::mat4 view, glm::mat4 projection) override;

        glm::mat4 getModelMatrix() override;

        std::shared_ptr<Instance>
        create(std::string id, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 origin) override;
    };
}

#endif //PUZZLE_GAME_ENGINE_SIMPLEMODEL_H
