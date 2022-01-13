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
        "cube_grass_side",
        std::make_shared<engine::SimpleModel>(
            "cube_grass_side",
            "resources/objects/blocks/cube_grass_side/cube_grass_side.obj",
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
            "cube_grass_corner_single",
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
        "cube_grass_side_single",
        std::make_shared<engine::SimpleModel>(
            "cube_grass_side_single",
            "resources/objects/blocks/cube_grass_side_single/cube_grass_side_single.obj",
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
        "cube_grass_side_bottom",
        std::make_shared<engine::SimpleModel>(
            "cube_grass_side_bottom",
            "resources/objects/blocks/cube_grass_side_bottom/cube_grass_side_bottom.obj",
            shader,
            [](const std::string& id,
               glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 origin,
               glm::vec3 boundsMin, glm::vec3 boundsMax) -> std::shared_ptr<engine::Instance> {
                return std::make_shared<BlockInstance>(
                    id, pos, rot, scale, origin, boundsMin, boundsMax);
            }
        )
    );

    factory->registerModel(
        "cube_grass_center_bottom",
        std::make_shared<engine::SimpleModel>(
            "cube_grass_center_bottom",
            "resources/objects/blocks/cube_grass_center_bottom/cube_grass_center_bottom.obj",
            shader,
            [](const std::string& id,
               glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 origin,
               glm::vec3 boundsMin, glm::vec3 boundsMax) -> std::shared_ptr<engine::Instance> {
                return std::make_shared<BlockInstance>(
                    id, pos, rot, scale, origin, boundsMin, boundsMax);
            }
        )
    );

    factory->registerModel(
        "cube_grass_corner_bottom",
        std::make_shared<engine::SimpleModel>(
            "cube_grass_corner_bottom",
            "resources/objects/blocks/cube_grass_corner_bottom/cube_grass_corner_bottom.obj",
            shader,
            [](const std::string& id,
               glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 origin,
               glm::vec3 boundsMin, glm::vec3 boundsMax) -> std::shared_ptr<engine::Instance> {
                return std::make_shared<BlockInstance>(
                    id, pos, rot, scale, origin, boundsMin, boundsMax);
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
        "water_center",
        std::make_shared<engine::LodModel>(
            "water_center",
            std::vector<std::string>{
                "resources/objects/blocks/water_center/lod_1/water_center.obj",
                "resources/objects/blocks/water_center/lod_2/water_center.obj"
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

    auto cubeGrassCenterBlocks = mapGround(
        factory, "cube_grass_center", "cube_grass_center_",
        glm::ivec3(-6, -1, -8), 8 * 2, 8 * 2, 2,
        std::vector<glm::ivec3>{
            glm::ivec3(0, -1, 0), glm::ivec3(2, -1, 0),
            glm::ivec3(2, -1, -2), glm::ivec3(0, -1, -2)
        });

    game.blocks.insert(game.blocks.begin(), cubeGrassCenterBlocks.begin(), cubeGrassCenterBlocks.end());

    auto gs1 = mapGround(
        factory, "cube_grass_side", "cube_grass_side_",
        glm::ivec3(-6, -1, 8), 8 * 2, 1 * 2, 2,
        std::vector<glm::ivec3>{}
    );
    game.blocks.insert(game.blocks.end(), gs1.begin(), gs1.end());
    auto gs2 = mapGround(
        factory, "cube_grass_side", "cube_grass_side_",
        glm::ivec3(-6, -1, -8), 8 * 2, 1 * 2, 2,
        std::vector<glm::ivec3>{}, glm::vec3(0, 180, 0), 8
    );
    game.blocks.insert(game.blocks.end(), gs2.begin(), gs2.end());
    auto gs3 = mapGround(
        factory, "cube_grass_side", "cube_grass_side_",
        glm::ivec3(-8, -1, -6), 1 * 2, 7 * 2, 2,
        std::vector<glm::ivec3>{}, glm::vec3(0, 270, 0), 16
    );
    game.blocks.insert(game.blocks.end(), gs3.begin(), gs3.end());
    auto gs4 = mapGround(
        factory, "cube_grass_side", "cube_grass_side_",
        glm::ivec3(10, -1, -6), 1 * 2, 7 * 2, 2,
        std::vector<glm::ivec3>{}, glm::vec3(0, 90, 0), 23
    );
    game.blocks.insert(game.blocks.end(), gs4.begin(), gs4.end());


    // auto b = factory->createInstance("cube_grass_center", "c");
    // b->position.y = -2;
    // auto b2 = factory->createInstance("cube_grass_corner", "c2");
    // b2->position.z = -1;
    // blocks.push_back(b);
    // blocks.push_back(b2);

    // Cube Grass Corner
    // -----------------
    auto cgcId = -1;
    std::vector<glm::vec3> cgcPositions = {
        glm::vec3(-8, -1, 8), glm::vec3(10, -1, 8),
        glm::vec3(-8, -1, -8), glm::vec3(10, -1, -8)
    };
    std::vector<glm::vec3> cgcRotations = {
        glm::vec3(0, 0, 0), glm::vec3(0, 90, 0),
        glm::vec3(0, 270, 0), glm::vec3(0, 180, 0)
    };
    std::vector<std::shared_ptr<engine::Instance>> cgcBlocks;
    for (int i = 0; i < cgcPositions.size(); ++i) {
        auto instanceId = "cube_grass_corner" + std::to_string(++cgcId);
        auto instance = factory->createInstance("cube_grass_corner", instanceId);
        instance->position = cgcPositions[i];
        instance->rotation = cgcRotations[i];
        cgcBlocks.push_back(std::move(instance));
    }
    game.blocks.insert(game.blocks.begin(), cgcBlocks.begin(), cgcBlocks.end());

    // Bridges
    // -------
    auto bridgeId = -1;
    std::vector<glm::vec3> bridgePositions = {
        glm::vec3(4, 0, 0), glm::vec3(4, 0, -2), glm::vec3(4, 0, -4),
        glm::vec3(2, 1, -4), glm::vec3(0, 1, -4), glm::vec3(-2, 1, -4),
        glm::vec3(-2, 2, -2), glm::vec3(-2, 2, 0), glm::vec3(-2, 2, 2),
        glm::vec3(0, 3, 2), glm::vec3(2, 3, 2), glm::vec3(4, 3, 2),
        glm::vec3(4, 4, 0), glm::vec3(4, 4, -2), glm::vec3(4, 4, -4),
        glm::vec3(2, 5, -4), glm::vec3(0, 5, -4), glm::vec3(-10+9*2, -2, 10)
    };
    std::vector<glm::vec3> bridgeRotations = {
        glm::vec3(0, 90, 0), glm::vec3(0, 90, 0), glm::vec3(0, 90, 0),
        glm::vec3(0, 180, 0), glm::vec3(0, 180, 0), glm::vec3(0, 180, 0),
        glm::vec3(0, 270, 0), glm::vec3(0, 270, 0), glm::vec3(0, 270, 0),
        glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),
        glm::vec3(0, 90, 0), glm::vec3(0, 90, 0), glm::vec3(0, 90, 0),
        glm::vec3(0, 180, 0), glm::vec3(0, 180, 0), glm::vec3(0, 0, 0)
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

    // Cube Grass Corner Single
    // ------------------------
    auto cgcsId = -1;
    std::vector<glm::vec3> cgcsPositions = {
        glm::vec3(0, 6, 0), glm::vec3(2, 6, 0),
        glm::vec3(2, 6, -2), glm::vec3(0, 6, -2),
        glm::vec3(-10, -3, 10), glm::vec3(10, -3, 10), glm::vec3(-10, -3, -8),
        glm::vec3(-6, 0, 6), glm::vec3(-6, 0, 4),
        glm::vec3(-4, 0, 4), glm::vec3(-4, 0, 6)

    };
    std::vector<glm::vec3> cgcsRotations = {
        glm::vec3(0, 0, 0), glm::vec3(0, 90, 0),
        glm::vec3(0, 180, 0), glm::vec3(0, 270, 0),
        glm::vec3(0, 0, 0), glm::vec3(0, 90, 0), glm::vec3(0, 270, 0),
        glm::vec3(0, 0, 0), glm::vec3(0, 270, 0),
        glm::vec3(0, 180, 0), glm::vec3(0, 90, 0),
    };
    std::vector<std::shared_ptr<engine::Instance>> cgsBlocks;

    for (int i = 0; i < cgcsPositions.size(); ++i) {
        auto instanceId = "cube_grass_corner_single_" + std::to_string(++cgcsId);
        auto instance = factory->createInstance("cube_grass_corner_single", instanceId);
        instance->position = cgcsPositions[i];
        instance->rotation = cgcsRotations[i];
        cgsBlocks.push_back(std::move(instance));
    }
    game.blocks.insert(
        game.blocks.begin(), cgsBlocks.begin(), cgsBlocks.end()
    );

    // Cube Grass Side Single
    // ----------------------
    auto cgssBlocks1 = mapGround(
        factory, "cube_grass_side_single", "cube_grass_side_single_",
        glm::ivec3(-8, -3, 10), 9 * 2, 1 * 2, 2,
        std::vector<glm::ivec3>{}, glm::vec3(0, 0, 0), 50
    );
    game.blocks.insert(game.blocks.end(), cgssBlocks1.begin(), cgssBlocks1.end());
    auto cgssBlocks2 = mapGround(
        factory, "cube_grass_side_single", "cube_grass_side_single_",
        glm::ivec3(-10, -3, -6), 1 * 2, 8 * 2, 2,
        std::vector<glm::ivec3>{}, glm::vec3(0, 270, 0), 60
    );
    game.blocks.insert(game.blocks.end(), cgssBlocks2.begin(), cgssBlocks2.end());

    // auto bridge = factory->createInstance("bridge", "bridge_1");
    // bridge->position = glm::vec3(2, 0, 2);
    // game.blocks.push_back(bridge);

    // Water Center
    // ------------
    auto wc1 = mapGround(
        factory, "water_center", "water_center_",
        glm::ivec3(-10, -1, 10), 11 * 2, 1 * 2, 2,
        std::vector<glm::ivec3>{}, glm::vec3(0, 0, 0)
    );
    auto wc2 = mapGround(
        factory, "water_center", "water_center_",
        glm::ivec3(-10, -1, 10), 11 * 2, 1 * 2, 2,
        std::vector<glm::ivec3>{}, glm::vec3(90, 0, 0), 20
    );
    auto wc3 = mapGround(
        factory, "water_center", "water_center_",
        glm::ivec3(-10, -1, -8), 1 * 2, 9 * 2, 2,
        std::vector<glm::ivec3>{}, glm::vec3(0, 0, 0), 40
    );
    auto wc4 = mapGround(
        factory, "water_center", "water_center_",
        glm::ivec3(-10, -1, -8), 1 * 2, 10 * 2, 2,
        std::vector<glm::ivec3>{}, glm::vec3(0, 0, 90), 60
    );
    auto wcId = 80;
    std::vector<glm::vec3> wcPositions = {
        glm::vec3(-10+11*2, -1, 10), glm::vec3(-10, -1, -8),

    };
    std::vector<glm::vec3> wcRotations = {
        glm::vec3(90, 0, 90), glm::vec3(270, 0, 0),
    };
    std::vector<std::shared_ptr<engine::Instance>> wc5;
    for (int i = 0; i < wcPositions.size(); ++i) {
        auto instanceId = "water_center_" + std::to_string(++wcId);
        auto instance = factory->createInstance("water_center", instanceId);
        instance->position = wcPositions[i];
        instance->rotation = wcRotations[i];
        wc5.push_back(std::move(instance));
    }

    // Cube Grass Side Bottom
    // ----------------------
    auto gsb1 = mapGround(
        factory, "cube_grass_side_bottom", "cube_grass_side_bottom_",
        glm::ivec3(-6, -3, 8), 8 * 2, 1 * 2, 2,
        std::vector<glm::ivec3>{}
    );
    game.blocks.insert(game.blocks.end(), gsb1.begin(), gsb1.end());
    auto gsb2 = mapGround(
        factory, "cube_grass_side_bottom", "cube_grass_side_bottom_",
        glm::ivec3(-8, -3, -8), 9 * 2, 1 * 2, 2,
        std::vector<glm::ivec3>{}, glm::vec3(0, 180, 0), 8
    );
    game.blocks.insert(game.blocks.end(), gsb2.begin(), gsb2.end());
    auto gsb3 = mapGround(
        factory, "cube_grass_side_bottom", "cube_grass_side_bottom_",
        glm::ivec3(-8, -3, -6), 1 * 2, 8 * 2, 2,
        std::vector<glm::ivec3>{}, glm::vec3(0, 270, 0), 17
    );
    game.blocks.insert(game.blocks.end(), gsb3.begin(), gsb3.end());
    auto gsb4 = mapGround(
        factory, "cube_grass_side_bottom", "cube_grass_side_bottom_",
        glm::ivec3(10, -3, -6), 1 * 2, 8 * 2, 2,
        std::vector<glm::ivec3>{}, glm::vec3(0, 90, 0), 25
    );
    game.blocks.insert(game.blocks.end(), gsb4.begin(), gsb4.end());

    // Cube Grass Corner Bottom
    // ------------------------
    auto cgcb = factory->createInstance("cube_grass_corner_bottom", "cube_grass_corner_bottom_0");
    cgcb->position = glm::vec3(-8+9*2, -3, -8);
    cgcb->rotation = glm::vec3(0, 180, 0);

    // Cube Grass Center Bottom
    // ------------------------
    auto cgcbBlocks = mapGround(
        factory, "cube_grass_center_bottom", "cube_grass_center_bottom_",
        glm::ivec3(-6, -3, -8), 8 * 2, 8 * 2, 2,
        std::vector<glm::ivec3>{
            glm::ivec3(0, -3, 0), glm::ivec3(2, -3, 0),
            glm::ivec3(2, -3, -2), glm::ivec3(0, -3, -2)
        });

    game.blocks.insert(game.blocks.begin(), cgcbBlocks.begin(), cgcbBlocks.end());
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
