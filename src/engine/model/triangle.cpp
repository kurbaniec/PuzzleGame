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
    ) : instance(std::move(instance)), mesh(mesh), vertices(std::move(vertices)), offset(offset), shader(shader) {}

    glm::vec3& Triangle::updateCentroid() {
        auto modelMatrix = instance->modelMatrix;
        // Calculate centroid
        // See: https://brilliant.org/wiki/triangles-centroid/
        auto localCentroid
            = (vertices[0].get().Position + vertices[1].get().Position + vertices[2].get().Position) * 1.0f / 3.0f;
        // Calculate centroid "vertex" with model (composition) matrix
        // Note: Order is important p' = Mp
        // -----------------------------------------------------------
        // vec3 to vec4 (homogenization) See: https://stackoverflow.com/a/13690159/12347616
        // vec4 to vec3 See: https://stackoverflow.com/a/18842386/12347616
        centroid = glm::vec3(modelMatrix * glm::vec4(localCentroid, 1.0f));
        return centroid;
    }

    float Triangle::updateCameraDistance(glm::vec3 cameraPosition) {
        // Calculate distance
        // See: https://stackoverflow.com/a/55984640/12347616
        // See: https://learnopengl.com/Advanced-OpenGL/Blending
        cameraDistance = glm::length(cameraPosition - centroid);
        return cameraDistance;
    }

    void Triangle::draw(glm::mat4 view, glm::mat4 projection) {
        shader->use();
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);
        shader->setMat4("model", instance->modelMatrix);
        const_cast<Mesh&>(mesh).drawTriangle(shader, offset);
    }

    Triangle::Triangle(Triangle&& source) noexcept
        : instance(source.instance), mesh(source.mesh), vertices(source.vertices),
          offset(source.offset), shader(source.shader), centroid(source.centroid),
          cameraDistance(source.cameraDistance) {}

    Triangle& Triangle::operator=(Triangle&& other) noexcept {
        if (this != &other) {
            auto& i = const_cast<std::shared_ptr<Instance>&>(instance);
            i = other.instance;
            auto& m = const_cast<Mesh&>(mesh);
            auto& otherM = const_cast<Mesh&>(other.mesh);
            m = std::move(otherM);
            auto& v = const_cast<std::vector<std::reference_wrapper<Vertex>>&>(vertices);
            auto& otherV = const_cast<std::vector<std::reference_wrapper<Vertex>>&>(other.vertices);
            v = std::move(otherV);
            auto& o = const_cast<unsigned int&>(offset);
            o = other.offset;
            centroid = other.centroid;
            cameraDistance = other.cameraDistance;
        }
        return *this;
    }

    Triangle& Triangle::operator=(const Triangle& other) noexcept {
        if (this != &other) {
            auto& i = const_cast<std::shared_ptr<Instance>&>(instance);
            i = other.instance;
            auto& m = const_cast<Mesh&>(mesh);
            auto& otherM = const_cast<Mesh&>(other.mesh);
            m = std::move(otherM);
            auto& v = const_cast<std::vector<std::reference_wrapper<Vertex>>&>(vertices);
            auto& otherV = const_cast<std::vector<std::reference_wrapper<Vertex>>&>(other.vertices);
            v = std::move(otherV);
            auto& o = const_cast<unsigned int&>(offset);
            o = other.offset;
            centroid = other.centroid;
            cameraDistance = other.cameraDistance;
        }
        return *this;
    }

    // Triangle& Triangle::operator=(Triangle& other) noexcept {
    //     if (this != &other) {
    //         // const std::shared_ptr<Instance> instance;
    //         // const Mesh& mesh;
    //         // const std::vector<std::reference_wrapper<Vertex>> vertices;
    //         // const unsigned int offset;
    //         // const std::shared_ptr<Shader> shader;
    //         // glm::vec3 centroid;
    //         // float cameraDistance;
    //         auto& i = const_cast<std::shared_ptr<Instance>&>(instance);
    //         i = other.instance;
    //         auto m = const_cast<const Mesh*>(&mesh);
    //         m = &other.mesh;
    //     }
    //     return *this;
    // }


}