//
// Created by kurbaniec on 23.12.2021.
//

#ifndef PUZZLE_GAME_ENGINE_TRIANGLE_H
#define PUZZLE_GAME_ENGINE_TRIANGLE_H

#include "mesh.h"
#include "../instance/instance.h"

namespace engine {
    class Triangle {
    public:
        const std::shared_ptr<Instance>& instance;
        const Mesh& mesh;
        const std::vector<std::reference_wrapper<Vertex>> vertices;
        const unsigned int offset;

        Triangle(
            std::shared_ptr<Instance>& instance,
            Mesh& mesh,
            std::vector<std::reference_wrapper<Vertex>> vertices,
            unsigned int offset
        );

        glm::vec3 centroid();
    };
}


#endif //PUZZLE_GAME_ENGINE_TRIANGLE_H
