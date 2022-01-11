//
// Created by kurbaniec on 22.12.2021.
//

#include "state.h"

#include <utility>

namespace engine {

    void State::addModel(const std::string& modelName, std::shared_ptr<Model> model) {
        if (models.contains(modelName)) {
            throw std::exception("Model with same name is already defined");
        }
        models[modelName] = std::move(model);
    }

    void State::addInstance(const std::string& id, std::shared_ptr<Instance> instance) {
        if (instances.contains(id)) {
            throw std::exception("Instance with same name is already defined");
        }
        instances[id] = std::move(instance);
    }

    void State::setCamera(std::shared_ptr<Camera> new_camera) {
        camera = std::move(new_camera);
    }

    void State::setWindow(std::shared_ptr<Window> new_window) {
        window = std::move(new_window);
    }

    void State::setKeys(std::shared_ptr<std::map<int, int>> new_keys) {
        keys = std::move(new_keys);
    }

    void State::setCurrentFrame(float currentFrame) {
        delta.deltaTime =  currentFrame - delta.lastFrame;
        delta.lastFrame = currentFrame;
    }

    std::shared_ptr<Model> State::getModel(const std::string& modelName) {
        if (models.contains(modelName)) {
            return models[modelName];
        }
        return nullptr;
    }

    std::shared_ptr<Instance> State::getInstance(const std::string& id) {
        if (instances.contains(id)) {
            return instances[id];
        }
        return nullptr;
    }

    std::shared_ptr<Camera> State::getCamera() const {
        return camera;
    }

    std::shared_ptr<Window> State::getWindow() const {
        return window;
    }

    std::shared_ptr<std::map<int, int>> State::getKeys() const {
        return keys;
    }

    float State::getDeltaTime() {
        return delta.deltaTime;
    }
}