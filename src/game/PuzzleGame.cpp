//
// Created by kurbaniec on 12.01.2022.
//

#include "PuzzleGame.h"
#include "../engine/model/lodmodel.h"
#include "../engine/factory/InstanceFactory.h"
#include "BlockInstance.h"

PuzzleGame::PuzzleGame(
    GLFWwindow* window,
    const std::shared_ptr<engine::State>& state
) : GameBasis(window, state) {}


void PuzzleGame::setup() {
    auto factory = std::make_shared<engine::InstanceFactory>(state);
    auto shader = std::make_shared<engine::Shader>("shader/backpack/vertex.glsl", "shader/backpack/fragment.glsl");
    auto camera = state->getCamera();

    factory->registerModel(
        "player_model",
        std::make_shared<engine::LodModel>(
            "player_model",
            std::vector<std::string>{
                "resources/objects/player/lod_1/player.obj",
                "resources/objects/player/lod_2/player.obj",
                "resources/objects/player/lod_3/player.obj",
                "resources/objects/player/lod_4/player.obj"},
            std::vector<float>{5, 10, 15, 20},
            std::vector<std::shared_ptr<engine::Shader>>{shader, shader, shader, shader},
            [](const std::string& id,
               glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 origin,
               glm::vec3 boundsMin, glm::vec3 boundsMax) -> std::shared_ptr<engine::Instance> {
                return std::make_shared<BlockInstance>(id, pos, rot, scale, origin, boundsMin, boundsMax);
            },
            camera
        )
    );

    factory->registerModel(
        "cube_grass_corner",
        std::make_shared<engine::SimpleModel>(
            "cube_grass_corner",
            "resources/objects/blocks/cube_grass_corner/cube_grass_corner.obj",
            shader,
            [](const std::string& id,
               glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 origin,
               glm::vec3 boundsMin, glm::vec3 boundsMax) -> std::shared_ptr<engine::Instance> {
                return std::make_shared<BlockInstance>(id, pos, rot, scale, origin, boundsMin, boundsMax);
            }
        )
    );

    factory->createInstance("player_model", "player");
    corner1 = std::dynamic_pointer_cast<BlockInstance>(
        factory->createInstance("cube_grass_corner", "cb_1"));
    corner2 = std::dynamic_pointer_cast<BlockInstance>(
        factory->createInstance("cube_grass_corner", "cb_2"));
    corner3 = std::dynamic_pointer_cast<BlockInstance>(
        factory->createInstance("cube_grass_corner", "cb_3"));
    corner4 = std::dynamic_pointer_cast<BlockInstance>(
        factory->createInstance("cube_grass_corner", "cb_4"));

    corner1->rotation.y = 270;

    corner2->rotation.y = 180;
    corner2->position.x = 2;


    corner3->rotation.y = 90;
    corner3->position.x = 2;
    corner3->position.z = 2;

    corner4->rotation.y = 0;
    corner4->position.z = 2;
}

void PuzzleGame::update() {
    // per-frame time logic
    // --------------------
    auto deltaTime = state->getDeltaTime();
    // Process user input (camera controls)
    // ------------------------------------
    processInput(deltaTime);
    // Update instance positions
    // -------------------------

}

void PuzzleGame::processInput(float deltaTime) {
    // Workaround to check if window is "focused"
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
        auto camera = state->getCamera();
        auto keys = state->getKeys();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        auto wPress = glfwGetKey(window, GLFW_KEY_W);
        if (wPress == GLFW_PRESS)
            camera->ProcessKeyboard(engine::FORWARD, deltaTime);
        auto sPress = glfwGetKey(window, GLFW_KEY_S);
        if (sPress == GLFW_PRESS)
            camera->ProcessKeyboard(engine::BACKWARD, deltaTime);
        auto aPress = glfwGetKey(window, GLFW_KEY_A);
        if (aPress == GLFW_PRESS)
            camera->ProcessKeyboard(engine::LEFT, deltaTime);
        auto dPress = glfwGetKey(window, GLFW_KEY_D);
        if (dPress == GLFW_PRESS)
            camera->ProcessKeyboard(engine::RIGHT, deltaTime);
        auto spacePress = glfwGetKey(window, GLFW_KEY_SPACE);
        if (!keys->contains(GLFW_KEY_SPACE))
            keys->insert({GLFW_KEY_SPACE, GLFW_RELEASE});
        if (keys->at(GLFW_KEY_SPACE) == GLFW_RELEASE && spacePress == GLFW_PRESS) {
            camera->toggleMode();
        }

        // Clear is needed because insert does not overwrite existing keys
        keys->clear();
        keys->insert(
            {
                {GLFW_KEY_W,     wPress},
                {GLFW_KEY_S,     sPress},
                {GLFW_KEY_A,     aPress},
                {GLFW_KEY_D,     dPress},
                {GLFW_KEY_SPACE, spacePress}
            }
        );
    }
}

