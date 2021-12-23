//
// Created by kurbaniec on 23.12.2021.
//

#ifndef PUZZLE_GAME_ENGINE_TRIANGLE_H
#define PUZZLE_GAME_ENGINE_TRIANGLE_H

#include "mesh.h"
#include "../instance/instance.h"

namespace engine {
    class Triangle {
    public:
        const std::weak_ptr<Instance> instance;
        const Mesh& mesh;
        const std::vector<std::reference_wrapper<Vertex>> vertices;
        const unsigned int offset;
        const std::shared_ptr<Shader>& shader;

        Triangle(
            std::shared_ptr<Instance> instance,
            Mesh& mesh,
            std::vector<std::reference_wrapper<Vertex>> vertices,
            unsigned int offset,
            std::shared_ptr<Shader>& shader
        );

        glm::vec3 centroid();

        void draw(glm::mat4 view, glm::mat4 projection);
    };
}


#endif //PUZZLE_GAME_ENGINE_TRIANGLE_H
