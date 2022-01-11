//
// Created by kurbaniec on 01.01.2022.
//

#include "lodmodel.h"

#include <utility>

namespace engine {

    LodModel::LodModel(
        const std::string& id,
        const std::vector<std::string>& paths,
        const std::vector<float>& distances, const std::vector<std::shared_ptr<Shader>>& shaders,
        const std::function<std::shared_ptr<Instance>
            (std::string, glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3)>& creator,
        std::shared_ptr<Camera> camera
    ) : Model(id, createLodCreatorLambda()), camera(std::move(camera)) {
        auto size = paths.size();
        if (size == 0) {
            throw std::runtime_error("Parameters cannot be empty");
        }
        if (size == distances.size() && size == shaders.size()) {
            models = std::map<float, SimpleModel>();
            for (auto i = 0; i < size; ++i) {
                auto distance = distances[i];
                auto simpleId = id + "_" + std::to_string(distance);
                auto path = paths[i];
                auto shader = shaders[i];
                models.insert({distance, SimpleModel(simpleId, path, shader, creator)});

                toRemove.emplace_back();
                toAdd.emplace_back();
            }
            /*// Copy vector to list & assign distances member field
            // See: https://www.techiedelight.com/convert-vector-list-cpp/
            std::copy(distances.begin(), distances.end(), std::back_inserter(this->distances));
            // Sort distances
            // See: https://stackoverflow.com/a/10652701/12347616
            this->distances.sort();*/
            this->distances = distances;
            std::sort(this->distances.begin(), this->distances.end());
        } else {
            throw std::runtime_error("Path/Distance/Shader size mismatch");
        }
        // Assign first lod bounding box as overall bounding box
        auto& model = models.at(distances[0]);
        boundsMin = model.boundingBoxMin();
        boundsMax = model.boundingBoxMax();
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
        (std::string, glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3)>
    LodModel::createLodCreatorLambda() {
        auto func = [this](
            const std::string& id,
            glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 origin,
            glm::vec3 boundsMin, glm::vec3 boundsMax
        ) -> std::shared_ptr<Instance> {
            return this->lodCreator(id, pos, rot, scale, origin);
        };
        return {func};
    }

    void LodModel::updateInstances() {
        auto distIndex = 0;
        auto distMax = distances.size() - 1;

        try {

            for (auto& distance: distances) {
                // SimpleModel has no default constructor
                // So one must use `at` instead of `[]` operator.
                // See: https://stackoverflow.com/a/12124339/12347616
                auto& model = models.at(distance);
                auto instances = model.getInstances();

                auto instanceIndex = 0;
                for (auto& instance: instances) {
                    auto instanceDistance = getCameraDistance(instance->position);
                    //std::cout << instanceDistance << std::endl;
                    if (instanceDistance <= distance) {
                        if (distIndex > 0) {
                            //auto currentDist = distance;
                            //auto newDist = distance;
                            auto newDistIndex = distIndex;

                            for (auto i = distIndex; i >= 0; --i) {
                                auto distanceCheck = distances[i];
                                if (instanceDistance <= distanceCheck) {
                                    //newDist = distanceCheck;
                                    newDistIndex = i;
                                } else {
                                    break;
                                }
                            }

                            // for (auto distanceCheck = distances.begin() + distCounter - 1;
                            //      distanceCheck != distances.begin(); --distanceCheck) {
                            //     if (*distanceCheck < instanceDistance) {
                            //         newDistance = *distanceCheck;
                            //         break;
                            //     }
                            // }

                            if (distIndex != newDistIndex) {
                                std::cout << "A " << distIndex << " " << newDistIndex << std::endl;
                                toRemove[distIndex].push_back(instanceIndex);
                                toAdd[newDistIndex].push_back(instance);
                            }

                        }
                    } else {
                        if (distIndex < distMax) {
                            //auto currentDist = distance;
                            //auto newDist = distance;
                            auto newDistIndex = distIndex;

                            for (auto i = distIndex; i <= distMax; ++i) {
                                auto distanceCheck = distances[i];
                                if (instanceDistance <= distanceCheck) {
                                    //newDist = distanceCheck;
                                    newDistIndex = i;
                                    break;
                                }
                            }

                            if (distIndex != newDistIndex) {
                                std::cout << "B " << distIndex << " " << newDistIndex << std::endl;
                                toRemove[distIndex].push_back(instanceIndex);
                                toAdd[newDistIndex].push_back(instance);
                            }
                        }
                    }
                    ++instanceIndex;
                }
                ++distIndex;
            }
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }

        distIndex = 0;
        for (auto& distance: distances) {
            auto& model = models.at(distance);
            auto& remove = toRemove[distIndex];
            if (!remove.empty()) {
                model.removeInstances(remove);
                remove.clear();
            }
            auto& add = toAdd[distIndex];
            if (!add.empty()) {
                model.addInstances(add);
                add.clear();
            }
            ++distIndex;
        }
    }

    void LodModel::drawInstances(glm::mat4 view, glm::mat4 projection) {
        updateInstances();
        for (auto&[_, model]: models) {
            model.drawInstances(view, projection);
        }
    }

    std::vector<std::reference_wrapper<Triangle>> LodModel::getTriangles() {
        transparentTrianglesRef.clear();
        for (auto&[_, model]: models) {
            auto triangles = model.getTriangles();
            transparentTrianglesRef.insert(
                std::end(transparentTrianglesRef),
                std::begin(triangles), std::end(triangles)
            );
        }
        return transparentTrianglesRef;
    }

    float LodModel::getCameraDistance(glm::vec3 position) {
        return glm::length(camera->position - position);
    }


}
