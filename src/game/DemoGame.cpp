//
// Created by kurbaniec on 11.01.2022.
//

#include "DemoGame.h"
#include "../engine/factory/InstanceFactory.h"
#include "../engine/model/simplemodel.h"
#include "BlockInstance.h"
#include "../engine/model/lodmodel.h"
#include "glm/gtx/string_cast.hpp"

DemoGame::DemoGame(
    GLFWwindow* window,
    const std::shared_ptr<engine::State>& state
) : GameBasis(window, state) {}


void DemoGame::setup() {
    auto factory = std::make_shared<engine::InstanceFactory>(state);
    // build and compile shaders
    auto shader = std::make_shared<engine::Shader>("shader/model/vertex.glsl", "shader/model/fragment.glsl");
    auto camera = state->getCamera();

    factory->registerModel(
        "blockModel",
        std::make_shared<engine::SimpleModel>(
            "blockModel",
            "resources/objects/block/transparentblock.obj",
            shader,
            [](const std::string& id,
               glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 origin,
               glm::vec3 boundsMin, glm::vec3 boundsMax) -> std::shared_ptr<engine::Instance> {
                return std::make_shared<BlockInstance>(id, pos, rot, scale, origin, boundsMin, boundsMax);
            }
        )
    );
    factory->registerModel(
        "blockLodModel",
        std::make_shared<engine::LodModel>(
            "blockLodModel",
            std::vector<std::string>{
                "resources/objects/block/transparentblock.obj",
                "resources/objects/block2/transparentblock.obj"},
            std::vector<float>{5, 10},
            std::vector<std::shared_ptr<engine::Shader>>{shader, shader},
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

    factory->createInstance("blockModel", "test");
    factory->createInstance("blockModel", "test2");
    factory->createInstance("blockLodModel", "test3");
    factory->createInstance("player_model", "player");
    factory->createInstance("cube_grass_corner", "cb");


    // Cast to derived class
    // See: https://stackoverflow.com/a/14545746/12347616
    block1 = std::dynamic_pointer_cast<BlockInstance>(state->getInstance("test"));
    block2 = std::dynamic_pointer_cast<BlockInstance>(state->getInstance("test2"));
    block3 = std::dynamic_pointer_cast<BlockInstance>(state->getInstance("test3"));
    player = std::dynamic_pointer_cast<BlockInstance>(state->getInstance("player"));
    grass = std::dynamic_pointer_cast<BlockInstance>(state->getInstance("cb"));
}

void DemoGame::update() {
    // per-frame time logic
    // --------------------
    auto deltaTime = state->getDeltaTime();
    // Process user input (camera controls)
    // ------------------------------------
    processInput(deltaTime);
    // Update instance positions
    // -------------------------
    grass->position.y = -5;
    player->position.y = -10;

    block3->position.z += deltaTime * 0.5f;
    block3->rotation.y += deltaTime * 10.0f;

    block2->position.y = 2;

    // See: https://stackoverflow.com/a/34104944/12347616
    if (!glm::all(glm::lessThan(block1->scale, glm::vec3(0.2f)))) {
        block1->scale -= deltaTime * 0.002f;
    }
    block1->rotation.y += deltaTime * 10.0f;
    block1->rotation.x += deltaTime * 10.0f;

    std::cout << glm::to_string(block3->forward) << std::endl;
}

// Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void DemoGame::processInput(float deltaTime) {
    // Workaround to check if window is "focused"
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
        auto camera = state->getCamera();
        auto keys = state->getKeys();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        auto wPress = glfwGetKey(window, GLFW_KEY_W);
        if (wPress == GLFW_PRESS)
            camera->processKeyboard(engine::FORWARD, deltaTime);
        auto sPress = glfwGetKey(window, GLFW_KEY_S);
        if (sPress == GLFW_PRESS)
            camera->processKeyboard(engine::BACKWARD, deltaTime);
        auto aPress = glfwGetKey(window, GLFW_KEY_A);
        if (aPress == GLFW_PRESS)
            camera->processKeyboard(engine::LEFT, deltaTime);
        auto dPress = glfwGetKey(window, GLFW_KEY_D);
        if (dPress == GLFW_PRESS)
            camera->processKeyboard(engine::RIGHT, deltaTime);
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

