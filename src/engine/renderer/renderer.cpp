//
// Created by kurbaniec on 23.12.2021.
//

#include "renderer.h"

namespace engine {

    Renderer::Renderer(std::shared_ptr<State> state): state(std::move(state)) {}

    void Renderer::draw() {
        // Get view & projection matrix
        auto viewMatrix = state->camera->GetViewMatrix();
        auto projectionMatrix = state->window->getProjectionMatrix();
        // Update instance model matrices
        for (auto& [id, instance]: state->instances) {
            instance->updateModelMatrix();
        }
        // Draw opaque non-transparent meshes
        for (auto& [modelName, model]: state->models) {
            model->drawInstances(viewMatrix, projectionMatrix);
        }
        // Draw transparent mesh triangles
    }
}