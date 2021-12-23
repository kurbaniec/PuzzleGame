//
// Created by kurbaniec on 23.12.2021.
//

#ifndef PUZZLE_GAME_ENGINE_TRIANGLE_H
#define PUZZLE_GAME_ENGINE_TRIANGLE_H

#include "mesh.h"

namespace engine {
    class Triangle {
    public:
        const std::vector<Vertex> vertices;
        const Mesh& mesh;
        const unsigned int offset;
        glm::mat4& modelMatrix;

        Triangle(std::vector<Vertex> vertices, Mesh& mesh, unsigned int offset, glm::mat4& modelMatrix);

        glm::vec3 centroid();
    };
}


#endif //PUZZLE_GAME_ENGINE_TRIANGLE_H
