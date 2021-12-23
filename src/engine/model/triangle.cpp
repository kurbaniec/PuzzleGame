//
// Created by kurbaniec on 23.12.2021.
//

#include "triangle.h"

namespace engine {

    Triangle::Triangle(
        std::vector<Vertex> vertices,
        Mesh& mesh,
        unsigned int offset,
        glm::mat4& modelMatrix
    ): vertices(std::move(vertices)), mesh(mesh), offset(offset), modelMatrix(modelMatrix) {

    }

    glm::vec3 Triangle::centroid() {
        // TODO
        return {1.0f, 1.0f, 1.0f};
    }


}