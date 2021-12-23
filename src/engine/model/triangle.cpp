//
// Created by kurbaniec on 23.12.2021.
//

#include "triangle.h"

#include <utility>
#include "../instance/instance.h"

namespace engine {

    Triangle::Triangle(
        std::shared_ptr<Instance> instance,
        Mesh& mesh,
        std::vector<std::reference_wrapper<Vertex>> vertices,
        unsigned int offset,
        std::shared_ptr<Shader>& shader
    ): instance(instance), mesh(mesh), vertices(std::move(vertices)), offset(offset), shader(shader) {}

    glm::vec3 Triangle::centroid() {
        // TODO
        return {1.0f, 1.0f, 1.0f};
    }

    void Triangle::draw(glm::mat4 view, glm::mat4 projection) {
        shader->use();
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);
        shader->setMat4("model", instance.lock()->modelMatrix);
        const_cast<Mesh&>(mesh).drawTriangle(shader, offset);
    }


}