//
// Created by kurbaniec on 21.12.2021.
//

#ifndef PUZZLE_GAME_ENGINE_SIMPLEMODEL_H
#define PUZZLE_GAME_ENGINE_SIMPLEMODEL_H

#ifndef PUZZLE_GAME_ENGINE_MODEL_H
#include "model.h"
#include "triangle.h"

#endif //PUZZLE_GAME_ENGINE_MODEL_H

namespace engine {
    class SimpleModel : public Model {
    public:
        explicit SimpleModel(
            const std::string& id,
            const std::string& path,
            std::shared_ptr<Shader> shader,
            std::function<std::shared_ptr<Instance>
                (std::string, glm::vec3, glm::vec3, glm::vec3, glm::vec3)> creator
        );

        void drawInstances(glm::mat4 view, glm::mat4 projection) override;

        std::vector<std::reference_wrapper<Triangle>> getTriangles() override;

        std::shared_ptr<Instance>
        create(std::string id, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 origin) override;

        const std::vector<std::shared_ptr<Instance>>& getInstances();

        void removeInstances(const std::vector<int>& indices);
        void addInstances(const std::vector<std::shared_ptr<Instance>>& instances);

    private:
        // Model Data
        std::vector<Mesh> meshes;
        std::vector<Mesh> transparentMeshes;
        std::vector<Triangle> transparentTriangles;
        std::vector<std::reference_wrapper<Triangle>> transparentTrianglesRef;
        std::shared_ptr<Shader> shader;
        std::vector<Texture> texturesLoaded;
        // Managed Instances
        std::vector<std::shared_ptr<Instance>> instances;
    };
}

#endif //PUZZLE_GAME_ENGINE_SIMPLEMODEL_H
