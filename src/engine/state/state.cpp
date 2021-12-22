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
}