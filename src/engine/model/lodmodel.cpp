//
// Created by kurbaniec on 01.01.2022.
//

#include "lodmodel.h"

namespace engine {

    LodModel::LodModel(
        const std::string& id,
        const std::vector<std::string>& paths,
        const std::vector<float>& distances, const std::vector<std::shared_ptr<Shader>>& shaders,
        std::function<std::shared_ptr<Instance>
            (std::string, glm::vec3, glm::vec3, glm::vec3, glm::vec3)> creator,
        std::shared_ptr<Camera> camera
    ) : Model(id, createLodCreatorLambda()) {
        auto size = paths.size();
        if (size == 0) {
            throw std::runtime_error("Config cannot be empty");
        }
        if (size == distances.size() && size == shaders.size()) {
            models = std::map<float, SimpleModel>();
            for (auto i = 0; i < size; ++i) {

            }
        } else {
            throw std::runtime_error("Path/Distance/Shader size mismatch");
        }
    }

    std::shared_ptr<Instance>
    LodModel::lodCreator(
        const std::string& id,
        glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 origin
    ) {
        auto instanceDistance = getCameraDistance(pos);
        auto i = 1;
        auto modelCount = models.size();
        for (auto &[distance, model]: models) {
            if (instanceDistance < distance || i == modelCount) {
                return model.create(id, pos, rot, scale, origin);
            }
            ++i;
        }
        throw std::runtime_error("No Creator for instance found");
    }

    std::function<std::shared_ptr<Instance>
        (std::string, glm::vec3, glm::vec3, glm::vec3, glm::vec3)>
    LodModel::createLodCreatorLambda() {
        auto func = [this](
            const std::string& id, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 origin
        ) -> std::shared_ptr<Instance> {
            return this->lodCreator(id, pos, rot, scale, origin);
        };
        return {func};
    }

    void LodModel::drawInstances(glm::mat4 view, glm::mat4 projection) {

    }

    std::vector<std::reference_wrapper<Triangle>> LodModel::getTriangles() {
        return transparentTrianglesRef;
    }

    float LodModel::getCameraDistance(glm::vec3 position) {
        return glm::length(camera->Position - position);
    }


}
