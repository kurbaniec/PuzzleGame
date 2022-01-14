#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utils/print.h"
#include "utils/model.h"

#include "engine/model/simplemodel.h"
#include "engine/factory/InstanceFactory.h"
#include "engine/camera/camera.h"
#include "engine/renderer/renderer.h"
#include "game/DemoGame.h"
#include "game/PuzzleGame.h"


// Special Thanks!
// ===============
// * https://learnopengl.com/
// * https://quaternius.com/packs/ultimateplatformer.html
// * https://en.cppreference.com/w/

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void cursor_enter_callback(GLFWwindow* window, int entered);
// void processInput(GLFWwindow* window);
// void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void window_focus_callback(GLFWwindow* window, int focused);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();

    // Not needed, uses highest version automatically
    // See: https://www.reddit.com/r/opengl/comments/14kocr/comment/c7eo4l4/?utm_source=share&utm_medium=web2x&context=3
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Settings & State management
    // ---------------------------
    const unsigned int SCR_WIDTH = 1280;
    const unsigned int SCR_HEIGHT = 720;

    auto state = std::make_shared<engine::State>();
    auto camera = std::make_shared<engine::Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    auto projection = std::make_shared<engine::Window>(SCR_WIDTH, SCR_HEIGHT, state);
    auto keys = std::make_shared<map<int, int>>();
    auto mouseMovement = std::make_shared<engine::MouseMovement>(
        static_cast<float>(projection->width), static_cast<float>(projection->height)
    );
    state->setCamera(camera);
    state->setWindow(projection);
    state->setKeys(keys);
    state->setMouseMovement(mouseMovement);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(
        projection->width, projection->height, "Puzzle Game", nullptr, nullptr
    );
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }



    glfwMakeContextCurrent(window);
    // Pass state to glfw
    // Node: Do not create void* from shared_ptr, leads to crash in release mode (msvc)
    // See: https://stackoverflow.com/questions/15578935/proper-way-of-casting-pointer-types
    // And: https://stackoverflow.com/a/61336206/12347616
    // And: https://www.reddit.com/r/cpp_questions/comments/d2owlo/comment/ezw398b/?utm_source=share&utm_medium=web2x&context=3
    glfwSetWindowUserPointer(window, static_cast<void*>(state.get()));
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    // glfwSetKeyCallback(window, key_callback);
    glfwSetCursorEnterCallback(window, cursor_enter_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    // Enable/Disable vsync
    // See: https://www.glfw.org/docs/latest/group__context.html#ga6d4e0cdf151b5e579bd67f13202994ed
    // glfwSwapInterval(0);
    // Force aspect ratio
    // See: https://www.glfw.org/docs/latest/group__window.html#ga72ac8cb1ee2e312a878b55153d81b937
    //glfwSetWindowAspectRatio(window, 16, 9);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    auto renderer = std::make_shared<engine::Renderer>(state);
    renderer->setup();

    // Set Game
    // --------
    //auto game = DemoGame(window, state);
    auto game = PuzzleGame(window, state);

    try {
        // Setup level
        game.setup();
        // Compute model matrices
        for (auto& instance: state->instances) {
            instance.second->updateModelMatrix();
        }
    } catch (const runtime_error& error) {
        std::cerr << error.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {

        // Update delta time
        state->setCurrentFrame(static_cast<float>(glfwGetTime()));
        // Clear screent
        renderer->clear();
        try {
            // Process input & game logic
            game.update();
            // Render
            renderer->draw();
        } catch (const runtime_error& error) {
            std::cerr << error.what() << std::endl;
            exit(EXIT_FAILURE);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}




// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    auto& state = *static_cast<engine::State*>(glfwGetWindowUserPointer(window));
    auto projection = state.getWindow();
    // Check when minimizing window
    if (height == 0) height = 1;
    projection->width = width;
    projection->height = height;
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    auto& state = *static_cast<engine::State*>(glfwGetWindowUserPointer(window));
    auto camera = state.getCamera();
    auto mouse = state.getMouseMovement();
    auto xPos = static_cast<float>(xpos);
    auto yPos = static_cast<float>(ypos);
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
        if (mouse->firstMouse) {
            mouse->lastX = xPos;
            mouse->lastY = yPos;
            mouse->firstMouse = false;
        }
        float xOffset = xPos - mouse->lastX;
        float yOffset = mouse->lastY - yPos; // reversed since y-coordinates go from bottom to top
        mouse->lastX = xPos;
        mouse->lastY = yPos;
        camera->processMouseMovement(xOffset, yOffset);
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    auto& state = *static_cast<engine::State*>(glfwGetWindowUserPointer(window));
    auto camera = state.getCamera();
    auto offset = static_cast<float>(yoffset);
    camera->processMouseScroll(offset);
}

// See: https://www.glfw.org/docs/3.3/input_guide.html#cursor_enter
void cursor_enter_callback(GLFWwindow* window, int entered) {
    if (entered) {
        // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        // The cursor entered the content area of the window
    }
}

// See: https://www.glfw.org/docs/latest/window_guide.html#window_focus
void window_focus_callback(GLFWwindow* window, int focused) {
    if (focused) {
        // The window gained input focus
        if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
}

/*
// toggle
bool firstMouse = true;
bool disable = false;
bool focus = true;

// Recommend way to handle key events
// See: https://www.glfw.org/docs/3.3/input_guide.html
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
        disable = !disable;
        print("Pressed Button 0", " | State: ", disable);
    }
    if (key == GLFW_KEY_0 && action == GLFW_RELEASE) {
        print("Released Button 0");
    }

}*/