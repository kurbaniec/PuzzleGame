//
// Created by kurbaniec on 23.12.2021.
//

#include "triangle.h"

#include <utility>
#include "../instance/instance.h"

namespace engine {

    Triangle::Triangle(
        std::shared_ptr<Instance>& instance,
        Mesh& mesh,
        std::vector<std::reference_wrapper<Vertex>> vertices,
        unsigned int offset
    ): instance(instance), mesh(mesh), vertices(std::move(vertices)), offset(offset) {}

    glm::vec3 Triangle::centroid() {
        // TODO
        return {1.0f, 1.0f, 1.0f};
    }


}