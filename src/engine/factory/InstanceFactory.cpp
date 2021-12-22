//
// Created by kurbaniec on 22.12.2021.
//

#include "InstanceFactory.h"

#include <utility>

namespace engine {

    InstanceFactory::InstanceFactory(std::shared_ptr<State> state) : state(std::move(state)) {}

    void InstanceFactory::registerModel(const std::string& modelName, std::shared_ptr<Model> model) {
        state->addModel(modelName, std::move(model));
    }

    void InstanceFactory::createInstance(
        const std::string& modelName, const std::string& id,
        glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 origin
    ) {
        auto model = state->getModel(modelName);
        if (model == nullptr) {
            throw std::runtime_error("No Model with name " + modelName + " found");
        }
        auto instance = model->create(id, position, rotation, scale, origin);
        if (instance == nullptr) {
            throw std::runtime_error("Instance is nullptr");
        }
        if (id != instance->id) {
            throw std::runtime_error("Id on created Instance");
        }
        auto instanceId = instance->id;
        state->addInstance(instanceId, std::move(instance));
    }


}