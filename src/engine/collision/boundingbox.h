//
// Created by kurbaniec on 06.01.2022.
//

#ifndef PUZZLE_GAME_ENGINE_BOUNDINGBOX_H
#define PUZZLE_GAME_ENGINE_BOUNDINGBOX_H


#include "glm/vec3.hpp"
#include "glm/ext/matrix_float4x4.hpp"

namespace engine {
    class BoundingBox {
    public:
        friend class Bounds;
        BoundingBox(glm::vec3& min, glm::vec3& max);

        [[nodiscard]] const glm::vec3& min() const;
        [[nodiscard]] const glm::vec3& max() const;
        [[nodiscard]] float height() const; // distance min/max y
        [[nodiscard]] float width() const; // distance min/max x
        [[nodiscard]] float depth() const; // distance min/max z


    private:
        glm::vec3& localMin;
        glm::vec3& localMax;
        glm::vec3 valMin;
        glm::vec3 valMax;

        void update(glm::mat4 modelMatrix);
    };

    class Bounds {
    public:
        Bounds(glm::vec3 min, glm::vec3 max);

        [[nodiscard]] const BoundingBox& local() const;
        [[nodiscard]] const BoundingBox& world() const;

        void setLocalBounds(glm::vec3 newMin, glm::vec3 max);
        void updateWorldBounds(glm::mat4 modelMatrix);

    private:
        glm::vec3 min;
        glm::vec3 max;

        BoundingBox localBb;
        BoundingBox worldBb;
    };
}


#endif //PUZZLE_GAME_ENGINE_BOUNDINGBOX_H
