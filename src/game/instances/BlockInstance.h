//
// Created by kurbaniec on 22.12.2021.
//

#ifndef PUZZLE_GAME_BLOCKINSTANCE_H
#define PUZZLE_GAME_BLOCKINSTANCE_H


#include "../../engine/instance/instance.h"

class BlockInstance : public engine::Instance {
public:
    BlockInstance(
        std::string id,
        glm::vec3 position,
        glm::vec3 rotation,
        glm::vec3 scale,
        glm::vec3 origin,
        glm::vec3 boundsMin, glm::vec3 boundsMax,
        std::set<std::string> tags = {}
    );
};


#endif //PUZZLE_GAME_BLOCKINSTANCE_H
