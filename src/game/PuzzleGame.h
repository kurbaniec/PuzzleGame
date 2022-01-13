//
// Created by kurbaniec on 12.01.2022.
//

#ifndef PUZZLE_GAME_PUZZLEGAME_H
#define PUZZLE_GAME_PUZZLEGAME_H


#include "GameBasis.h"
#include "BlockInstance.h"
#include "../engine/factory/InstanceFactory.h"
#include "Player.h"
#include <set>

class PuzzleGame : public GameBasis {
public:
    friend class PuzzleGameLevel;

    PuzzleGame(
        GLFWwindow* window,
        const std::shared_ptr<engine::State>& state
    );

    void setup() override;

    void update() override;

private:
    struct LevelPart {
        std::string id;
        std::string model;
        glm::vec3 position;
        glm::vec3 rotation;

        LevelPart(std::string id, std::string model, glm::vec3 position, glm::vec3 rotation) :
            id(std::move(id)), model(std::move(model)), position(position), rotation(rotation) {}
    };

    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<engine::Instance>> blocks;

    std::shared_ptr<BlockInstance> corner1;
    std::shared_ptr<BlockInstance> corner2;
    std::shared_ptr<BlockInstance> corner3;
    std::shared_ptr<BlockInstance> corner4;

    void processInput(float deltaTime);

    static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

    void setupLevel();

    std::vector<std::shared_ptr<engine::Instance>>
    mapGround(
        std::shared_ptr<engine::InstanceFactory> factory,
        std::string model, std::string idPrefix,
        glm::ivec3 start, int xSize, int zSize, int stepSize,
        std::vector<glm::ivec3> omit, glm::vec3 rotation = glm::vec3(0.0f), int id = -1
    );

    std::vector<std::shared_ptr<engine::Instance>>
    mapWallX(
        std::shared_ptr<engine::InstanceFactory> factory,
        std::string model, std::string idPrefix,
        glm::ivec3 start, int xSize, int ySize, int stepSize,
        std::vector<glm::ivec3> omit, glm::vec3 rotation = glm::vec3(0.0f), int id = -1
    );

    std::vector<std::shared_ptr<engine::Instance>>
    mapWallZ(
        std::shared_ptr<engine::InstanceFactory> factory,
        std::string model, std::string idPrefix,
        glm::ivec3 start, int zSize, int ySize, int stepSize,
        std::vector<glm::ivec3> omit, glm::vec3 rotation = glm::vec3(0.0f), int id = -1
    );
};


#endif //PUZZLE_GAME_PUZZLEGAME_H
