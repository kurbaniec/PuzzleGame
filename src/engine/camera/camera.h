//
// Source: https://learnopengl.com/Getting-started/Camera
//

#ifndef PUZZLE_GAME_ENGINE_CAMERA_H
#define PUZZLE_GAME_ENGINE_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace engine {

    // Defines several possible options for camera movement.
    // Used as abstraction to stay away from window-system specific input methods
    enum CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    enum Mode {
        FREE,
        ORBIT
    };

    // Default camera values
    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 2.5f;
    const float SENSITIVITY = 0.25f;
    const float ZOOM = 45.0f;
    const glm::vec3 TARGET = glm::vec3(0.0f);

    // An abstract camera class that processes input and calculates the
    // corresponding Euler Angles, Vectors and Matrices for use in OpenGL
    class Camera {
    public:

        // constructor with vectors
        Camera(
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
            float yaw = YAW, float pitch = PITCH,
            float speed = SPEED, float sensitivity = SENSITIVITY,
            float zoom = ZOOM,
            Mode mode = ORBIT, glm::vec3 target = TARGET
        );

        // constructor with scalar values
        Camera(
            float posX, float posY, float posZ,
            float upX, float upY, float upZ,
            float yaw, float pitch,
            Mode mode = ORBIT, glm::vec3 target = TARGET
        );

        // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
        void processKeyboard(CameraMovement direction, float deltaTime);

        // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
        void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

        // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
        void processMouseScroll(float yoffset);

        // returns the view matrix calculated using Euler Angles and the LookAt Matrix
        [[nodiscard]] glm::mat4 getViewMatrix() const;

        [[nodiscard]] Mode getCameraMode() const;

        [[nodiscard]] glm::vec3 getPosition() const;

        [[nodiscard]] glm::vec3 getTarget() const;

        [[nodiscard]] float getZoom() const;

        void toggleMode();

        void setPosition(glm::vec3 position);

        void setTarget(glm::vec3 target);

    private:
        glm::mat4 viewMatrix;
        // camera mode
        Mode mode;
        // camera Attributes
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;
        // euler Angles
        float yaw;
        float pitch;
        // camera options
        float movementSpeed;
        float mouseSensitivity;
        float zoom;
        // orbit camera options
        glm::vec3 target;


        static int sgn(double v);

        // calculates the front vector from the Camera's (updated) Euler Angles
        void updateCameraVectorsFree();

        void updateCameraVectorsOrbit();

        void updateCameraVectors();
    };

}

#endif //PUZZLE_GAME_ENGINE_CAMERA_H
