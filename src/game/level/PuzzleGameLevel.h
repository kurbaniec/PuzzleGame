//
// Created by kurbaniec on 13.01.2022.
//

#ifndef PUZZLE_GAME_PUZZLEGAMELEVEL_H
#define PUZZLE_GAME_PUZZLEGAMELEVEL_H

#include "../PuzzleGame.h"

class PuzzleGameLevel {
public:
    static void setupLevel(PuzzleGame& game);

    static std::vector<std::shared_ptr<engine::Instance>>
    mapGround(
        std::shared_ptr<engine::InstanceFactory> factory,
        std::string model, std::string idPrefix,
        glm::ivec3 start, int xSize, int zSize, int stepSize,
        std::vector<glm::ivec3> omit, glm::vec3 rotation = glm::vec3(0.0f), int id = -1
    );

    static std::vector<std::shared_ptr<engine::Instance>>
    mapWallX(
        std::shared_ptr<engine::InstanceFactory> factory,
        std::string model, std::string idPrefix,
        glm::ivec3 start, int xSize, int ySize, int stepSize,
        std::vector<glm::ivec3> omit, glm::vec3 rotation = glm::vec3(0.0f), int id = -1
    );

    static std::vector<std::shared_ptr<engine::Instance>>
    mapWallZ(
        std::shared_ptr<engine::InstanceFactory> factory,
        std::string model, std::string idPrefix,
        glm::ivec3 start, int zSize, int ySize, int stepSize,
        std::vector<glm::ivec3> omit, glm::vec3 rotation = glm::vec3(0.0f), int id = -1
    );
};


#endif //PUZZLE_GAME_PUZZLEGAMELEVEL_H
