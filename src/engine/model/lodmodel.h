//
// Created by kurbaniec on 01.01.2022.
//

#ifndef PUZZLE_GAME_ENGINE_LODMODEL_H
#define PUZZLE_GAME_ENGINE_LODMODEL_H

#include "model.h"

namespace engine {
    class LodModel : public Model {
    public:
        void drawInstances(glm::mat4 view, glm::mat4 projection) override;

        std::vector<std::reference_wrapper<Triangle>> getTriangles() override;

    private:

    };
}



#endif //PUZZLE_GAME_ENGINE_LODMODEL_H
