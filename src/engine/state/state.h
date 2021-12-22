//
// Created by kurbaniec on 22.12.2021.
//

#ifndef PUZZLE_GAME_ENGINE_STATE_H
#define PUZZLE_GAME_ENGINE_STATE_H

#include "../model/model.h"

namespace engine {
    class State {
    public:
        std::map<std::string, std::shared_ptr<Model>> models;
        std::map<std::string, std::shared_ptr<Instance>> instances;

        void addModel(const std::string& modelName, std::shared_ptr<Model> model);
        void addInstance(const std::string& id, std::shared_ptr<Instance> instance);

        std::shared_ptr<Model> getModel(const std::string& modelName);
        std::shared_ptr<Instance> getInstance(const std::string& id);
    };
}

#endif //PUZZLE_GAME_ENGINE_STATE_H