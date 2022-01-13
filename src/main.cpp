#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utils/print.h"
#include "utils/shader.h"
#include "utils/camera.h"
#include "utils/model.h"

#include "engine/model/simplemodel.h"
#include "engine/model/lodmodel.h"
#include "engine/instance/instance.h"
#include "game/BlockInstance.h"
#include "engine/state/state.h"
#include "engine/factory/InstanceFactory.h"
#include "engine/camera/camera.h"
#include "engine/renderer/renderer.h"
#include "game/DemoGame.h"
#include "game/PuzzleGame.h"


/*
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

double deltaTime;
double currentFrame;
double lastFrame;


int main() {
    std::cout << "Hello, World!" << std::endl;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(
            800, 600, "Puzzle Game", nullptr, nullptr
    );
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader("shader/vertex.glsl", "shader/fragment.glsl");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };

    // Vertex Array Object, Vertex Buffer Object, Element Buffer Object
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        // Get delta time
        // See: https://stackoverflow.com/a/12574822/12347616
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // print("Delta Time: ", deltaTime);

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

        // Draw in Polygon mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // Draw both triangles
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        // Draw first triangle
        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
        // Draw second triangle
        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT,  (void*)(3 * sizeof(GL_UNSIGNED_INT)));
        // glBindVertexArray(0); // no need to unbind it every time

        // Reste to default fill mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}
*/

// ==================================================
// Source: https://learnopengl.com/Model-Loading/Model

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void cursor_enter_callback(GLFWwindow* window, int entered);

void processInput(GLFWwindow* window);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void window_focus_callback(GLFWwindow* window, int focused);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// camera
//engine::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
// double deltaTime = 0.0f;
// double lastFrame = 0.0f;

// toggle
bool disable = false;
bool focus = true;

class ModelOld;

int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();

    // Not needed?
    // See: https://www.reddit.com/r/opengl/comments/14kocr/comment/c7eo4l4/?utm_source=share&utm_medium=web2x&context=3
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Puzzle Game", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    auto state = std::make_shared<engine::State>();
    auto camera = std::make_shared<engine::Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    auto projection = std::make_shared<engine::Window>(1280, 720, state);
    auto keys = std::make_shared<map<int, int>>();
    state->setCamera(camera);
    state->setWindow(projection);
    state->setKeys(keys);

    glfwMakeContextCurrent(window);
    // See: https://stackoverflow.com/a/61336206/12347616
    // And: https://www.reddit.com/r/cpp_questions/comments/d2owlo/comment/ezw398b/?utm_source=share&utm_medium=web2x&context=3
    auto glfwState = state;
    glfwSetWindowUserPointer(window, *reinterpret_pointer_cast<void*>(glfwState));
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
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

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    //stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    auto renderer = std::make_shared<engine::Renderer>(state);
    renderer->setup();

    // build and compile shaders
    // -------------------------
    ShaderOld shader("shader/backpack/vertex.glsl", "shader/backpack/fragment.glsl");
    auto shaderTest = std::make_shared<engine::Shader>("shader/backpack/vertex.glsl", "shader/backpack/fragment.glsl");

    // load models
    // -----------
    //Model ourModel(FileSystem::getPath("resources/objects/backpack/backpack.obj"));
    //Model ourModel("resources/objects/backpack/backpack.obj");
    //ModelOld m("resources/objects/block/transparentblock.obj");
    //ModelOld m2("resources/objects/block/transparentblock.obj");

    auto factory = std::make_shared<engine::InstanceFactory>(state);


    /*auto blockModel = state->getModel("blockModel");
    auto blockInstance = state->getInstance("test");
    auto blockInstance2 = state->getInstance("test2");
    auto blockInstance3 = state->getInstance("test3");

    auto cb = state->getInstance("cb");
    auto player = state->getInstance("player");*/

    // engine::SimpleModel mTest(
    //     "blockModel",
    //     "resources/objects/block/transparentblock.obj",
    //     shaderTest, true,
    //     [](const std::string& id, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 origin) -> shared_ptr<engine::Instance> {
    //         return std::make_shared<BlockInstance>(id, pos, rot, scale, origin);
    //     }
    // );


    // draw in wireframe
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) {
    // See: https://stackoverflow.com/a/23204968/12347616
    auto state = *static_cast<std::shared_ptr<engine::State>*>(glfwGetWindowUserPointer(window));
    auto camera = state->getCamera();
    auto keys = state->getKeys();
    auto deltaTime = state->getDeltaTime();
    if (focus) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            // glfwSetWindowShouldClose(window, true);
            focus = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        auto wPress = glfwGetKey(window, GLFW_KEY_W);
        if (wPress == GLFW_PRESS)
            camera->processKeyboard(engine::FORWARD, deltaTime);
        auto sPress = glfwGetKey(window, GLFW_KEY_S);
        if (sPress == GLFW_PRESS)
            camera->processKeyboard(engine::BACKWARD, deltaTime);
        auto aPress = glfwGetKey(window, GLFW_KEY_A);
        if (aPress == GLFW_PRESS)
            camera->processKeyboard(engine::LEFT, deltaTime);
        auto dPress = glfwGetKey(window, GLFW_KEY_D);
        if (dPress == GLFW_PRESS)
            camera->processKeyboard(engine::RIGHT, deltaTime);
        auto spacePress = glfwGetKey(window, GLFW_KEY_SPACE);
        if (!keys->contains(GLFW_KEY_SPACE))
            keys->insert({GLFW_KEY_SPACE, GLFW_RELEASE});
        if (keys->at(GLFW_KEY_SPACE) == GLFW_RELEASE && spacePress == GLFW_PRESS) {
            std::cout << "baum" << std::endl;
            camera->toggleMode();
        }

        /*if (glfwGetKey(window, GLFW_KEY_0) == GLFW_RELEASE) {
            print("Released Button 0");
        }*/

        // Clear is needed because insert does not overwrite existing keys
        keys->clear();
        keys->insert(
            {
                {GLFW_KEY_W, wPress}, {GLFW_KEY_S, sPress},
                { GLFW_KEY_A, aPress}, {GLFW_KEY_D, dPress},
                {GLFW_KEY_SPACE, spacePress}
            }
        );
    }
}

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

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    auto* state = static_cast<std::shared_ptr<engine::State>*>(glfwGetWindowUserPointer(window));
    auto projection = (*state)->getWindow();
    // Check when minimizing window
    if (height == 0) height = 1;
    projection->width = width;
    projection->height = height;
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    auto state = *static_cast<std::shared_ptr<engine::State>*>(glfwGetWindowUserPointer(window));
    auto camera = state->getCamera();

    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        camera->processMouseMovement(xoffset, yoffset);
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    auto state = *static_cast<std::shared_ptr<engine::State>*>(glfwGetWindowUserPointer(window));
    auto camera = state->getCamera();
    camera->processMouseScroll(yoffset);
}

// See: https://www.glfw.org/docs/3.3/input_guide.html#cursor_enter
void cursor_enter_callback(GLFWwindow* window, int entered) {
    if (entered) {
        // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        // The cursor entered the content area of the window

    }
    // else
    // {
    //     // The cursor left the content area of the window
    // }
}

// See: https://www.glfw.org/docs/latest/window_guide.html#window_focus
void window_focus_callback(GLFWwindow* window, int focused) {
    if (focused) {
        // The window gained input focus
        if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        //focus = true;
        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    // else {
    //     // The window lost input focus
    //     focus = false;
    // }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        //focus = true;
        // int width, height;
        // glfwGetWindowSize(window, &width, &height);
        // glfwSetCursorPos(window, width/2.0, height/2.0);
        // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}