//
// Created by kurbaniec on 22.12.2021.
//

#include "BlockInstance.h"

#include <utility>


BlockInstance::BlockInstance(
    std::string id,
    glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 origin,
    glm::vec3 boundsMin, glm::vec3 boundsMax
) : Instance(std::move(id), position, rotation, scale, origin, boundsMin, boundsMax) {

}
