//
// Created by kurbaniec on 23.12.2021.
//

#include "renderer.h"
#include "../model/triangle.h"

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/ext.hpp"

namespace engine {

    Renderer::Renderer(std::shared_ptr<State> state) : state(std::move(state)) {}

    void Renderer::draw() {
        // Get view & projection matrix
        // ----------------------------
        auto viewMatrix = state->camera->GetViewMatrix();
        auto projectionMatrix = state->window->getProjectionMatrix();
        // Update instance model matrices
        for (auto&[id, instance]: state->instances) {
            instance->updateModelMatrix();
        }
        // Draw opaque non-transparent meshes
        // ----------------------------------
        for (auto&[modelName, model]: state->models) {
            model->drawInstances(viewMatrix, projectionMatrix);
        }
        // Draw transparent mesh triangles
        // -------------------------------
        transparentTriangles.clear();
        for (auto&[modelName, model]: state->models) {
            // Combine vectors
            // See: std::vector<std::reference_wrapper<Triangle>>
            auto triangles = model->getTriangles();
            transparentTriangles.insert(transparentTriangles.end(), triangles.begin(), triangles.end());
        }
        auto cameraPos = state->camera->position;
        // std::cout << glm::to_string(cameraPos) << std::endl;
        for (auto triangle: transparentTriangles) {
            triangle.get().updateCentroid();
            triangle.get().updateCameraDistance(cameraPos);
        }

        std::sort(
            transparentTriangles.begin(), transparentTriangles.end(),
            [](std::reference_wrapper<Triangle> a, std::reference_wrapper<Triangle> b) {
                return a.get().cameraDistance > b.get().cameraDistance;
            }
        );

        //std::cout << "==========" << std::endl;
        for (auto triangle: transparentTriangles) {
            // std::cout << "Distance" << triangle.get().cameraDistance << std::endl;
            // std::cout << "Centroid" << glm::to_string(triangle.get().centroid) << std::endl;
            // std::cout << "Instance" << triangle.get().instance.lock()->id << std::endl;
            // std::cout << "Triangle Pos" << glm::to_string(
            //     triangle.get().vertices[0].get().Position + triangle.get().vertices[1].get().Position +
            //     triangle.get().vertices[1].get().Position) << std::endl;
            // std::cout << "Instance Pos" << glm::to_string(triangle.get().instance.lock()->position) << std::endl;
            triangle.get().draw(viewMatrix, projectionMatrix);
            //std::cout << "^^^^" << std::endl;
        }
        //std::cout << "==========" << std::endl;
    }
}