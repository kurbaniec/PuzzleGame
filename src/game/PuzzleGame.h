//
// Created by kurbaniec on 12.01.2022.
//

#ifndef PUZZLE_GAME_PUZZLEGAME_H
#define PUZZLE_GAME_PUZZLEGAME_H


#include "GameBasis.h"
#include "BlockInstance.h"
#include "../engine/factory/InstanceFactory.h"
#include <set>

class PuzzleGame : public GameBasis {
public:
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

    std::shared_ptr<BlockInstance> corner1;
    std::shared_ptr<BlockInstance> corner2;
    std::shared_ptr<BlockInstance> corner3;
    std::shared_ptr<BlockInstance> corner4;

    void processInput(float deltaTime);

    void setupLevel();

    std::vector<std::shared_ptr<engine::Instance>>
    mapLevel(
        std::shared_ptr<engine::InstanceFactory> factory,
        std::string model, std::string idPrefix,
        glm::ivec3 start, int xSize, int zSize, int stepSize,
        std::set<glm::ivec3> omit, glm::vec3 rotation = glm::vec3(0.0f)
    );
};


#endif //PUZZLE_GAME_PUZZLEGAME_H
