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
            (std::string, glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3)> creator
    ) : Model(id, std::move(creator)), shader(std::move(shader)) {
        loadModel(path, texturesLoaded, meshes, transparentMeshes);
    }

    void SimpleModel::drawInstances(glm::mat4 view, glm::mat4 projection) {
        // shader->use();
        /*for (auto& mesh: meshes)
            mesh.Draw(shader);*/
        shader->use();
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);
        for (auto& instance: instances) {
            shader->setMat4("model", instance->modelMatrix);
            for (auto& mesh: meshes)
                mesh.draw(shader);
        }
    }

    std::shared_ptr<Instance>
    SimpleModel::create(
        std::string id,
        glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 origin
    ) {
        auto instance = Model::create(id, position, rotation, scale, origin);
        instances.push_back(instance);
        createTriangles(instance);
        return instance;
    }

    std::vector<std::reference_wrapper<Triangle>> SimpleModel::getTriangles() {
        transparentTrianglesRef.clear();
        for (auto& triangle: transparentTriangles) {
            transparentTrianglesRef.emplace_back(std::ref(triangle));
        }
        return transparentTrianglesRef;
    }

    const std::vector<std::shared_ptr<Instance>>& SimpleModel::getInstances() {
        return instances;
    }

    void SimpleModel::addInstances(const std::vector<std::shared_ptr<Instance>>& new_instances) {
        // Add collection to existing one
        // See: https://stackoverflow.com/a/2551785/12347616
        instances.insert(std::end(instances), std::begin(new_instances), std::end(new_instances));
        for (auto& instance: new_instances) {
            createTriangles(instance);
        }
    }

    void SimpleModel::removeInstances(std::vector<int>& indices) {
        // Two loop are needed because `erase` modifies the `instances` vector
        // and for `removeTriangles` we need to get the instance first with the original index
        for (auto& index: indices) {
            auto instance = instances[index];
            removeTriangles(instance->id);
        }
        // Sort indices before removal so that index to delete is always valid
        // See: https://stackoverflow.com/q/9025084/12347616
        std::sort(indices.begin(), indices.end(), std::greater<>());
        for (auto& index: indices) {
            instances.erase(instances.begin() + index);
        }
    }

    void SimpleModel::createTriangles(const std::shared_ptr<Instance>& instance) {
        for (auto& mesh: transparentMeshes) {
            for (auto i = 0, offset = 0; i < mesh.indices.size(); i += 3, ++offset) {
                std::vector<std::reference_wrapper<Vertex>> vertices{
                    std::ref(mesh.vertices[mesh.indices[i]]),
                    std::ref(mesh.vertices[mesh.indices[i + 1]]),
                    std::ref(mesh.vertices[mesh.indices[i + 2]]),
                };
                transparentTriangles.emplace_back(instance, mesh, vertices, offset, shader);
            }
        }
    }

    void SimpleModel::removeTriangles(const std::string& instanceId) {
        // Triangle needs to implement Move assignment in order to work
        // See: https://stackoverflow.com/a/21813528/12347616
        transparentTriangles.erase(
            std::remove_if(
                transparentTriangles.begin(), transparentTriangles.end(),
                [instanceId](Triangle& triangle) -> bool {
                    return triangle.instance.lock()->id == instanceId;
                }), transparentTriangles.end()
        );
    }

}
