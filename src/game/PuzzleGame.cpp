//
// Created by kurbaniec on 12.01.2022.
//

#include "PuzzleGame.h"

#include "level/PuzzleGameLevel.h"

PuzzleGame::PuzzleGame(
    GLFWwindow* window,
    const std::shared_ptr<engine::State>& state
) : GameBasis(window, state), blocks(), stars() {
    camera = state->getCamera();
}


void PuzzleGame::setup() {
    PuzzleGameLevel::setupLevel(*this);
    // camera->setSensitivity(0.5);
    camera->setSpeed(5);
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
    // Player falling detection
    if (player->position.y < -15) {
        reset();
    }
    // Update player & enemy positions
    player->update(deltaTime);
    for (auto& enemy: enemies) {
        enemy->update(deltaTime);
    }
    // Collision detection
    for (auto& block: blocks) {
        if (player->intersectsAabb(block)) {
            player->solveCollision(block);
        }
    }
    // Enemy collision
    for (auto& enemy: enemies) {
        if (player->intersectsAabb(enemy)) {
            // Enemy hit, reset game
            reset();
        }
    }
    // Star collection
    for (auto& star: stars) {
        if (star->enabled) {
            if (player->intersectsAabb(star)) {
                star->enabled = false;
                ++starsCollected;
                // All stars collected, reset game
                if (starsCollected == stars.size()) reset();
            }
        }
    }
    // Match camera target with player height
    camera->setTarget(glm::vec3(0.0f, player->position.y, 0.0f));
}

// Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void PuzzleGame::processInput(float deltaTime) {
    // Workaround to check if window is "focused"
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
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
            camera->processKeyboard(engine::FORWARD, deltaTime);
        auto downPress = glfwGetKey(window, GLFW_KEY_DOWN);
        if (downPress == GLFW_PRESS)
            camera->processKeyboard(engine::BACKWARD, deltaTime);
        auto leftPress = glfwGetKey(window, GLFW_KEY_LEFT);
        if (leftPress == GLFW_PRESS)
            camera->processKeyboard(engine::LEFT, deltaTime);
        auto rightPress = glfwGetKey(window, GLFW_KEY_RIGHT);
        if (rightPress == GLFW_PRESS)
            camera->processKeyboard(engine::RIGHT, deltaTime);
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

void PuzzleGame::reset() {
    player->reset();
    for (auto& star: stars) {
        star->enabled = true;
    }
    starsCollected = 0;
}

void PuzzleGame::scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    auto& state = *static_cast<engine::State*>(glfwGetWindowUserPointer(window));
    auto camera = state.getCamera();
    auto deltaTime = state.getDeltaTime();
    auto offset = static_cast<float>(yOffset);
    if (camera->getMode() == engine::FREE) {
        camera->processMouseScroll(offset);
    } else {
        const int factor = 5;
        if (yOffset > 0) {
            camera->processKeyboard(engine::FORWARD, deltaTime * offset * factor);
        } else if (yOffset < 0) {
            camera->processKeyboard(engine::BACKWARD, deltaTime * glm::abs(offset) * factor);
        }

    }
}



