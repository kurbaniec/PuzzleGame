//
// Created by kurbaniec on 12.01.2022.
//

#include "PuzzleGame.h"

#include <utility>
#include "../engine/model/lodmodel.h"
#include "../engine/factory/InstanceFactory.h"
#include "BlockInstance.h"
#include "Player.h"
#include "level/PuzzleGameLevel.h"

PuzzleGame::PuzzleGame(
    GLFWwindow* window,
    const std::shared_ptr<engine::State>& state
) : GameBasis(window, state), blocks() {}


void PuzzleGame::setup() {
    //setupLevel();
    PuzzleGameLevel::setupLevel(*this);
    glfwSetScrollCallback(window, scrollCallback);
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
    player->update(deltaTime);

    for (auto& block: blocks) {
        if (player->intersectsAabb(block)) {
            // std::cout << "Intersect!" << std::endl;
            player->solveCollision(block);
        }

    }

    // std::cout << player->bounds().aabb().height() << std::endl;
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
        auto sPress = glfwGetKey(window, GLFW_KEY_S);
        auto aPress = glfwGetKey(window, GLFW_KEY_A);
        auto dPress = glfwGetKey(window, GLFW_KEY_D);
        player->input = glm::vec2(wPress - sPress, aPress - dPress);

        auto upPress = glfwGetKey(window, GLFW_KEY_UP);
        if (upPress == GLFW_PRESS)
            camera->ProcessKeyboard(engine::FORWARD, deltaTime);
        auto downPress = glfwGetKey(window, GLFW_KEY_DOWN);
        if (downPress == GLFW_PRESS)
            camera->ProcessKeyboard(engine::BACKWARD, deltaTime);
        auto leftPress = glfwGetKey(window, GLFW_KEY_LEFT);
        if (leftPress == GLFW_PRESS)
            camera->ProcessKeyboard(engine::LEFT, deltaTime);
        auto rightPress = glfwGetKey(window, GLFW_KEY_RIGHT);
        if (rightPress == GLFW_PRESS)
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
            {{GLFW_KEY_SPACE, spacePress}}
        );
    }
}


void PuzzleGame::setupLevel() {
    auto factory = std::make_shared<engine::InstanceFactory>(state);
    auto shader = std::make_shared<engine::Shader>(
        "shader/backpack/vertex.glsl", "shader/backpack/fragment.glsl");
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
            std::vector<float>{5, 8, 14, 25},
            std::vector<std::shared_ptr<engine::Shader>>{shader, shader, shader, shader},
            [](const std::string& id,
               glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 origin,
               glm::vec3 boundsMin, glm::vec3 boundsMax) -> std::shared_ptr<engine::Instance> {
                scale = scale * 0.4f;
                return std::make_shared<Player>(id, pos, rot, scale, origin, boundsMin, boundsMax);
            },
            camera
        )
    );

    factory->registerModel(
        "cube_grass_center",
        std::make_shared<engine::SimpleModel>(
            "cube_grass_center",
            "resources/objects/blocks/cube_grass_center/cube_grass_center.obj",
            shader,
            [](const std::string& id,
               glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 origin,
               glm::vec3 boundsMin, glm::vec3 boundsMax) -> std::shared_ptr<engine::Instance> {
                return std::make_shared<BlockInstance>(id, pos, rot, scale, origin, boundsMin, boundsMax);
            }
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
        "fire_corner",
        std::make_shared<engine::LodModel>(
            "fire_corner",
            std::vector<std::string>{
                "resources/objects/blocks/fire_corner/lod_1/fire_corner.obj",
                "resources/objects/blocks/fire_corner/lod_2/fire_corner.obj"
            },
            std::vector<float>{14, 15},
            std::vector<std::shared_ptr<engine::Shader>>{shader, shader},
            [](const std::string& id,
               glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 origin,
               glm::vec3 boundsMin, glm::vec3 boundsMax) -> std::shared_ptr<engine::Instance> {
                return std::make_shared<BlockInstance>(id, pos, rot, scale, origin, boundsMin, boundsMax);
            },
            camera
        )
    );

    int cornerId = -1;
    auto cornerMap = std::vector<LevelPart>{
        {
            std::string("cube_grass_corner_") + std::to_string(++cornerId),
            std::string("cube_grass_corner"),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0, 270, 0)
        },
        {
            std::string("cube_grass_corner_") + std::to_string(++cornerId),
            std::string("cube_grass_corner"),
            glm::vec3(2.0f, 0.0f, 0.0f),
            glm::vec3(0, 180, 0)
        },
        {
            std::string("cube_grass_corner_") + std::to_string(++cornerId),
            std::string("cube_grass_corner"),
            glm::vec3(2.0f, 0.0f, 2.0f),
            glm::vec3(0, 90, 0)
        },
        {
            std::string("cube_grass_corner_") + std::to_string(++cornerId),
            std::string("cube_grass_corner"),
            glm::vec3(0.0f, 0.0f, 2.0f),
            glm::vec3(0, 0, 0)
        },
    };


    // std::vector<std::shared_ptr<engine::Instance>> corners;
    //
    // for (auto& part: cornerMap) {
    //     auto instance = factory->createInstance(part.model, part.id);
    //     instance->position = part.position;
    //     instance->rotation = part.rotation;
    //     corners.push_back(std::move(instance));
    // }

    player = std::dynamic_pointer_cast<Player>(
        factory->createInstance("player_model", "player"));
    player->position.z = 1;


    //auto fireCube1 = factory->createInstance("fire_corner", "fire_corner_1");
    //auto fireCube2 = factory->createInstance("fire_corner", "fire_corner_2");
    //auto fireCube3 = factory->createInstance("fire_corner", "fire_corner_3");
    //auto fireCube4 = factory->createInstance("fire_corner", "fire_corner_4");

    auto fireCubes1 = mapWallX(
        factory, "fire_corner", "fire_corner_",
        glm::ivec3(-2, -4, 0), 1 * 2, 5 * 2, 2,
        std::vector<glm::ivec3>{});


    auto cubeCrassCenterBlocks = mapGround(
        factory, "cube_grass_center", "cube_grass_center_",
        glm::ivec3(-4, -1, -6), 5 * 2, 5 * 2, 2,
        std::vector<glm::ivec3>{
            glm::ivec3(0, -1, 0), glm::ivec3(2, -1, 0),
            glm::ivec3(2, -1, -2), glm::ivec3(0, -1, -2)
        });



    // auto b = factory->createInstance("cube_grass_center", "c");
    // b->position.y = -2;
    // auto b2 = factory->createInstance("cube_grass_corner", "c2");
    // b2->position.z = -1;
    // blocks.push_back(b);
    // blocks.push_back(b2);

    blocks.insert(
        blocks.begin(), cubeCrassCenterBlocks.begin(), cubeCrassCenterBlocks.end()
    );



    /*factory->createInstance("player_model", "player");
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
    corner4->position.z = 2;*/
}

std::vector<std::shared_ptr<engine::Instance>>
PuzzleGame::mapGround(
    std::shared_ptr<engine::InstanceFactory> factory, std::string model, std::string idPrefix,
    glm::ivec3 start, int xSize, int zSize, int stepSize, std::vector<glm::ivec3> omit, glm::vec3 rotation, int id
) {
    std::vector<std::shared_ptr<engine::Instance>> instances;
    for (int x = 0; x < xSize; x += stepSize) {
        for (int z = 0; z < zSize; z += stepSize) {
            auto position = start;
            position.x += x;
            position.z += z;
            if (omit.empty() || std::find(omit.begin(), omit.end(), position) == omit.end()) {
                auto instanceId = idPrefix + std::to_string(++id);
                auto instance = factory->createInstance(model, instanceId);
                instance->position = position;
                instance->rotation = rotation;
                instances.push_back(std::move(instance));
            }
        }
    }

    return instances;
}

std::vector<std::shared_ptr<engine::Instance>>
PuzzleGame::mapWallX(std::shared_ptr<engine::InstanceFactory> factory, std::string model, std::string idPrefix,
                     glm::ivec3 start, int xSize, int ySize, int stepSize, std::vector<glm::ivec3> omit,
                     glm::vec3 rotation, int id) {
    std::vector<std::shared_ptr<engine::Instance>> instances;
    for (int x = 0; x < xSize; x += stepSize) {
        for (int y = 0; y < ySize; y += stepSize) {
            auto position = start;
            position.x += x;
            position.y += y;
            if (omit.empty() || std::find(omit.begin(), omit.end(), position) == omit.end()) {
                auto instanceId = idPrefix + std::to_string(++id);
                auto instance = factory->createInstance(model, instanceId);
                instance->position = position;
                instance->rotation = rotation;
                instances.push_back(std::move(instance));
            }
        }
    }

    return instances;
}

std::vector<std::shared_ptr<engine::Instance>>
PuzzleGame::mapWallZ(std::shared_ptr<engine::InstanceFactory> factory, std::string model, std::string idPrefix,
                     glm::ivec3 start, int zSize, int ySize, int stepSize, std::vector<glm::ivec3> omit,
                     glm::vec3 rotation, int id) {
    std::vector<std::shared_ptr<engine::Instance>> instances;
    for (int z = 0; z < zSize; z += stepSize) {
        for (int y = 0; y < ySize; y += stepSize) {
            auto position = start;
            position.z += z;
            position.y += y;
            if (omit.empty() || std::find(omit.begin(), omit.end(), position) == omit.end()) {
                auto instanceId = idPrefix + std::to_string(++id);
                auto instance = factory->createInstance(model, instanceId);
                instance->position = position;
                instance->rotation = rotation;
                instances.push_back(std::move(instance));
            }
        }
    }

    return instances;
}

void PuzzleGame::scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    auto state = *static_cast<std::shared_ptr<engine::State>*>(glfwGetWindowUserPointer(window));
    auto camera = state->getCamera();
    auto deltaTime = state->getDeltaTime();
    auto offset = static_cast<float>(yOffset);
    if (camera->mode == engine::FREE) {
        camera->ProcessMouseScroll(offset);
    } else {
        const int factor = 5;
        if (yOffset > 0) {
            camera->ProcessKeyboard(engine::FORWARD, deltaTime * offset * factor);
        } else if (yOffset < 0) {
            camera->ProcessKeyboard(engine::BACKWARD, deltaTime * glm::abs(offset) * factor);
        }

    }

}



