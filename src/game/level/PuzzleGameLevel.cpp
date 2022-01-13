//
// Created by kurbaniec on 13.01.2022.
//

#include "PuzzleGameLevel.h"
#include "../../engine/model/lodmodel.h"

void PuzzleGameLevel::setupLevel(PuzzleGame& game) {
    // Required modules
    // ---------------
    auto factory = std::make_shared<engine::InstanceFactory>(game.state);
    auto shader = std::make_shared<engine::Shader>(
        "shader/backpack/vertex.glsl", "shader/backpack/fragment.glsl");
    auto camera = game.state->getCamera();

    // Factories
    // ---------
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
                return std::make_shared<BlockInstance>(
                    id, pos, rot, scale, origin, boundsMin, boundsMax, std::set<std::string>({"jump"}));
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
                return std::make_shared<BlockInstance>(
                    id, pos, rot, scale, origin, boundsMin, boundsMax, std::set<std::string>({"jump"}));
            }
        )
    );

    factory->registerModel(
        "cube_grass_corner_single",
        std::make_shared<engine::SimpleModel>(
            "cube_grass_corner",
            "resources/objects/blocks/cube_grass_corner_single/cube_grass_corner_single.obj",
            shader,
            [](const std::string& id,
               glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 origin,
               glm::vec3 boundsMin, glm::vec3 boundsMax) -> std::shared_ptr<engine::Instance> {
                return std::make_shared<BlockInstance>(
                    id, pos, rot, scale, origin, boundsMin, boundsMax, std::set<std::string>({"jump"}));
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
            std::vector<float>{25, 26},
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
        "bridge",
        std::make_shared<engine::LodModel>(
            "bridge",
            std::vector<std::string>{
                "resources/objects/blocks/bridge/lod_1/bridge.obj",
                "resources/objects/blocks/bridge/lod_2/bridge.obj"
            },
            std::vector<float>{25, 26},
            std::vector<std::shared_ptr<engine::Shader>>{shader, shader},
            [](const std::string& id,
               glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 origin,
               glm::vec3 boundsMin, glm::vec3 boundsMax) -> std::shared_ptr<engine::Instance> {
                return std::make_shared<BlockInstance>(
                    id, pos, rot, scale, origin, boundsMin, boundsMax, std::set<std::string>({"jump"})
                );
            },
            camera
        )
    );

    // Instances
    // ---------

    game.player = std::dynamic_pointer_cast<Player>(
        factory->createInstance("player_model", "player"));
    game.player->position.z = 1;


    //auto fireCube1 = factory->createInstance("fire_corner", "fire_corner_1");
    //auto fireCube2 = factory->createInstance("fire_corner", "fire_corner_2");
    //auto fireCube3 = factory->createInstance("fire_corner", "fire_corner_3");
    //auto fireCube4 = factory->createInstance("fire_corner", "fire_corner_4");


    // auto fireCubes1 = mapWallX(
    //     factory, "fire_corner", "fire_corner_",
    //     glm::ivec3(0, 0, 0), 1 * 2, 1 * 2, 2,
    //     std::vector<glm::ivec3>{}, glm::vec3(0, 270, 0));

    auto fireCubes1 = mapWallX(
        factory, "fire_corner", "fire_corner_",
        glm::ivec3(0, -4, 0), 1 * 2, 5 * 2, 2,
        std::vector<glm::ivec3>{}, glm::vec3(0, 270, 0));
    auto fireCubes2 = mapWallX(
        factory, "fire_corner", "fire_corner_",
        glm::ivec3(0, -4, -2), 1 * 2, 5 * 2, 2,
        std::vector<glm::ivec3>{}, glm::vec3(0, 180, 0), 5);
    auto fireCubes3 = mapWallX(
        factory, "fire_corner", "fire_corner_",
        glm::ivec3(2, -4, -2), 1 * 2, 5 * 2, 2,
        std::vector<glm::ivec3>{}, glm::vec3(0, 90, 0), 10);
    auto fireCubes4 = mapWallX(
        factory, "fire_corner", "fire_corner_",
        glm::ivec3(2, -4, 0), 1 * 2, 5 * 2, 2,
        std::vector<glm::ivec3>{}, glm::vec3(0, 0, 0), 15);

    game.blocks.insert(game.blocks.begin(), fireCubes1.begin(), fireCubes1.end());
    game.blocks.insert(game.blocks.begin(), fireCubes2.begin(), fireCubes2.end());
    game.blocks.insert(game.blocks.begin(), fireCubes3.begin(), fireCubes3.end());
    game.blocks.insert(game.blocks.begin(), fireCubes4.begin(), fireCubes4.end());

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

    game.blocks.insert(
        game.blocks.begin(), cubeCrassCenterBlocks.begin(), cubeCrassCenterBlocks.end()
    );

    auto bridgeId = -1;
    std::vector<glm::vec3> bridgePositions = {
        glm::vec3(4, 0, 0), glm::vec3(4, 0, -2), glm::vec3(4, 0, -4),
        glm::vec3(2, 1, -4), glm::vec3(0, 1, -4), glm::vec3(-2, 1, -4),
        glm::vec3(-2, 2, -2), glm::vec3(-2, 2, 0), glm::vec3(-2, 2, 2),
        glm::vec3(0, 3, 2), glm::vec3(2, 3, 2), glm::vec3(4, 3, 2),
        glm::vec3(4, 4, 0), glm::vec3(4, 4, -2), glm::vec3(4, 4, -4),
        glm::vec3(2, 5, -4), glm::vec3(0, 5, -4),
    };
    std::vector<glm::vec3> bridgeRotations = {
        glm::vec3(0, 90, 0), glm::vec3(0, 90, 0), glm::vec3(0, 90, 0),
        glm::vec3(0, 180, 0), glm::vec3(0, 180, 0), glm::vec3(0, 180, 0),
        glm::vec3(0, 270, 0), glm::vec3(0, 270, 0), glm::vec3(0, 270, 0),
        glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),
        glm::vec3(0, 90, 0), glm::vec3(0, 90, 0), glm::vec3(0, 90, 0),
        glm::vec3(0, 180, 0), glm::vec3(0, 180, 0),
    };
    std::vector<std::shared_ptr<engine::Instance>> bridges;

    for (int i = 0; i < bridgePositions.size(); ++i) {
        auto instanceId = "bridge_" + std::to_string(++bridgeId);
        auto instance = factory->createInstance("bridge", instanceId);
        instance->position = bridgePositions[i];
        instance->rotation = bridgeRotations[i];
        bridges.push_back(std::move(instance));
    }

    game.blocks.insert(
        game.blocks.begin(), bridges.begin(), bridges.end()
    );

    auto gcsId = -1;
    std::vector<glm::vec3> gcsPositions = {
        glm::vec3(0, 6, 0), glm::vec3(2, 6, 0),
        glm::vec3(2, 6, -2), glm::vec3(0, 6, -2)
    };
    std::vector<glm::vec3> gcsRotations = {
        glm::vec3(0, 0, 0), glm::vec3(0, 90, 0),
        glm::vec3(0, 180, 0), glm::vec3(0, 270, 0)
    };
    std::vector<std::shared_ptr<engine::Instance>> gcsBlocks;

    for (int i = 0; i < gcsPositions.size(); ++i) {
        auto instanceId = "cube_grass_corner_single_" + std::to_string(++gcsId);
        auto instance = factory->createInstance("cube_grass_corner_single", instanceId);
        instance->position = gcsPositions[i];
        instance->rotation = gcsRotations[i];
        gcsBlocks.push_back(std::move(instance));
    }

    game.blocks.insert(
        game.blocks.begin(), gcsBlocks.begin(), gcsBlocks.end()
    );

    // auto bridge = factory->createInstance("bridge", "bridge_1");
    // bridge->position = glm::vec3(2, 0, 2);
    // game.blocks.push_back(bridge);


}

std::vector<std::shared_ptr<engine::Instance>>
PuzzleGameLevel::mapGround(
    std::shared_ptr<engine::InstanceFactory> factory, std::string model, std::string idPrefix,
    glm::ivec3 start, int xSize, int zSize, int stepSize, std::vector<glm::ivec3> omit,
    glm::vec3 rotation, int id) {
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
PuzzleGameLevel::mapWallZ(
    std::shared_ptr<engine::InstanceFactory> factory, std::string model, std::string idPrefix,
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

std::vector<std::shared_ptr<engine::Instance>>
PuzzleGameLevel::mapWallX(
    std::shared_ptr<engine::InstanceFactory> factory, std::string model, std::string idPrefix,
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
