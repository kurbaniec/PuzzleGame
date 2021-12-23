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

    glm::vec3& Triangle::updateCentroid() {
        auto modelMatrix = instance.lock()->modelMatrix;
        // vec3 to vec4 (homogenization)
        // See: https://stackoverflow.com/questions/13690070/how-can-i-transform-a-glmvec3-by-a-glmmat4
        // vec4 to vec3
        // See: https://stackoverflow.com/a/18842386/12347616
        auto a = glm::vec3(glm::vec4(vertices[0].get().Position, 1.0f) * modelMatrix);
        auto b = glm::vec3(glm::vec4(vertices[1].get().Position, 1.0f) * modelMatrix);
        auto c = glm::vec3(glm::vec4(vertices[2].get().Position, 1.0f) * modelMatrix);
        // Calculate centroid
        // See: https://brilliant.org/wiki/triangles-centroid/
        centroid = (a+b+c) * 1.0f/3.0f;
        return centroid;
    }

    float Triangle::updateCameraDistance(glm::vec3 cameraPosition) {
        // Calculate distance
        // See: https://stackoverflow.com/a/55984640/12347616
        // See: https://learnopengl.com/Advanced-OpenGL/Blending
        cameraDistance = glm::length(cameraPosition - centroid );
        return cameraDistance;
    }

    void Triangle::draw(glm::mat4 view, glm::mat4 projection) {
        shader->use();
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);
        shader->setMat4("model", instance.lock()->modelMatrix);
        const_cast<Mesh&>(mesh).drawTriangle(shader, offset);
    }


}