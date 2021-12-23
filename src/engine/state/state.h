//
// Created by kurbaniec on 22.12.2021.
//

#ifndef PUZZLE_GAME_ENGINE_STATE_H
#define PUZZLE_GAME_ENGINE_STATE_H

#include "../model/model.h"
#include "../camera/camera.h"
#include "../window/window.h"

namespace engine {
    class Window;

    class State {
    public:
        std::map<std::string, std::shared_ptr<Model>> models;
        std::map<std::string, std::shared_ptr<Instance>> instances;
        std::shared_ptr<Camera> camera;
        std::shared_ptr<Window> window;

        void addModel(const std::string& modelName, std::shared_ptr<Model> model);
        void addInstance(const std::string& id, std::shared_ptr<Instance> instance);
        void setCamera(std::shared_ptr<Camera> camera);
        void setWindow(std::shared_ptr<Window> window);

        std::shared_ptr<Model> getModel(const std::string& modelName);
        std::shared_ptr<Instance> getInstance(const std::string& id);
        std::shared_ptr<Camera> getCamera() const;
        std::shared_ptr<Window> getWindow() const;
    };
}

#endif //PUZZLE_GAME_ENGINE_STATE_H
