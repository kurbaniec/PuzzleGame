//
// Created by kurbaniec on 22.12.2021.
//

#ifndef PUZZLE_GAME_ENGINE_INSTANCEFACTORY_H
#define PUZZLE_GAME_ENGINE_INSTANCEFACTORY_H

#include <string>
#include <memory>
#include "../model/model.h"
#include "../state/state.h"

namespace engine {
    class InstanceFactory {
    public:
        explicit InstanceFactory(std::shared_ptr<State> state);

        void registerModel(const std::string& modelName, std::shared_ptr<Model> model);
        void createInstance(
            const std::string& modelName,
            const std::string& id,
            glm::vec3 position = glm::vec3(0.0f),
            glm::vec3 rotation = glm::vec3(0.0f),
            glm::vec3 scale = glm::vec3(1.0f),
            glm::vec3 origin = glm::vec3(0.0f)
        );

    private:
        std::shared_ptr<State> state;
    };
}

#endif //PUZZLE_GAME_ENGINE_INSTANCEFACTORY_H
