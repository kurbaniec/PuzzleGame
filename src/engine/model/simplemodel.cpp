//
// Created by kurbaniec on 21.12.2021.
//

#include <string>
#include "simplemodel.h"
#include "triangle.h"

namespace engine {

    SimpleModel::SimpleModel(
        const std::string& id,
        const std::string& path,
        std::shared_ptr<Shader> shader,
        std::function<std::shared_ptr<Instance>
            (std::string, glm::vec3, glm::vec3, glm::vec3, glm::vec3)> creator
    ) : Model(id, std::move(shader), std::move(creator)) {
        loadModel(path, textures_loaded, meshes, transparentMeshes);
    }

    void SimpleModel::drawInstances(glm::mat4 view, glm::mat4 projection) {
        // shader->use();
        /*for (auto& mesh: meshes)
            mesh.Draw(shader);*/
        shader->use();
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);
        for (auto& instance: instances) {
            shader->setMat4("model", instance->getModelMatrix());
            for (auto& mesh: meshes)
                mesh.draw(shader);
        }
        // TODO: Move to transparent render
        for (auto& instance: instances) {
            shader->setMat4("model", instance->getModelMatrix());
            for (auto& mesh: transparentMeshes)
                mesh.draw(shader);
        }
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
        auto instance = Model::create(id, position, rotation, scale, origin);
        instances.push_back(instance);
        for (auto& mesh: transparentMeshes) {
            for (auto i = 0, offset = 0; i < mesh.indices.size(); i+=3, ++offset) {
                std::vector<std::reference_wrapper<Vertex>> vertices {
                    std::ref(mesh.vertices[mesh.indices[i]]),
                    std::ref(mesh.vertices[mesh.indices[i+1]]),
                    std::ref(mesh.vertices[mesh.indices[i+2]]),
                };
                transparentTriangles.emplace_back(vertices, mesh, offset, instance->getModelMatrix());
            }
        }
        return instance;
    }

    std::vector<std::reference_wrapper<Triangle>> SimpleModel::getTriangles() {
        transparentTrianglesRef.clear();
        for(auto& triangle: transparentTriangles) {
            transparentTrianglesRef.emplace_back(std::ref(triangle));
        }
        return transparentTrianglesRef;
    }

}
