//
// Created by kurbaniec on 23.12.2021.
//

#include "renderer.h"
#include "../model/triangle.h"

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/ext.hpp"

namespace engine {

    Renderer::Renderer(std::shared_ptr<State> state) : state(std::move(state)) {}


    void Renderer::setup() {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // draw in wireframe
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    void Renderer::clear() {
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::draw() {
        // Get view & projection matrix
        // ----------------------------
        auto viewMatrix = state->camera->getViewMatrix();
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
            auto& triangles = model->getTriangles();
            transparentTriangles.insert(transparentTriangles.end(), triangles.begin(), triangles.end());
        }
        auto cameraPos = state->camera->getPosition();
        // std::cout << glm::to_string(cameraPos) << std::endl;
        for (auto& triangle: transparentTriangles) {
            triangle.get().updateCentroid();
            triangle.get().updateCameraDistance(cameraPos);
        }

        std::sort(
            transparentTriangles.begin(), transparentTriangles.end(),
            [](std::reference_wrapper<Triangle> a, std::reference_wrapper<Triangle> b) {
                return a.get().cameraDistance > b.get().cameraDistance;
            }
        );

        for (auto& triangle: transparentTriangles) {
            triangle.get().draw(viewMatrix, projectionMatrix);
        }
    }
}