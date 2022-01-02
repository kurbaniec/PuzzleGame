//
// Created by kurbaniec on 01.01.2022.
//

#ifndef PUZZLE_GAME_ENGINE_LODMODEL_H
#define PUZZLE_GAME_ENGINE_LODMODEL_H

#include "model.h"
#include "simplemodel.h"
#include "../camera/camera.h"

namespace engine {
    class LodModel : public Model {
    public:

        explicit LodModel(
            const std::string& id,
            const std::vector<std::string>& paths,
            const std::vector<float>& distances,
            const std::vector<std::shared_ptr<Shader>>& shaders,
            const std::function<std::shared_ptr<Instance>
                (std::string, glm::vec3, glm::vec3, glm::vec3, glm::vec3)>& creator,
            std::shared_ptr<Camera> camera
        );

        void drawInstances(glm::mat4 view, glm::mat4 projection) override;

        std::vector<std::reference_wrapper<Triangle>> getTriangles() override;

    private:
        std::map<float, SimpleModel> models;
        //std::list<float> distances;
        std::vector<float> distances;
        std::vector<std::reference_wrapper<Triangle>> transparentTrianglesRef;
        std::shared_ptr<Camera> camera;

        std::vector<std::vector<int>> toRemove;
        std::vector<std::vector<std::shared_ptr<Instance>>> toAdd;

        std::shared_ptr<Instance>
        lodCreator(const std::string& id, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 origin);
        std::function<std::shared_ptr<Instance>
            (std::string, glm::vec3, glm::vec3, glm::vec3, glm::vec3)>
        createLodCreatorLambda();

        void updateInstances();

        float getCameraDistance(glm::vec3 position);
    };
}


#endif //PUZZLE_GAME_ENGINE_LODMODEL_H
