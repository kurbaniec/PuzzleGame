//
// Created by kurbaniec on 23.12.2021.
//

#include "camera.h"

namespace engine {

    Camera::Camera(
        glm::vec3 position, glm::vec3 up,
        float yaw, float pitch, float speed, float sensitivity, float zoom
    ) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(speed),
        MouseSensitivity(sensitivity), Zoom(zoom) {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    Camera::Camera(
        float posX, float posY, float posZ,
        float upX, float upY, float upZ,
        float yaw, float pitch
    ) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
        MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    glm::mat4 Camera::GetViewMatrix() const {
        // return glm::lookAt(Position, Position + Front, Up);
        return glm::lookAt(Position, glm::vec3(2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }


    void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
        /*xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch) {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();*/

        // Orbit camera
        // See: https://asliceofrendering.com/camera/2019/11/30/ArcballCamera/
        auto pos = glm::vec4(Position, 1.0f);
        auto point = glm::vec3(2.0f);
        auto pivot = glm::vec4(point, 1.0f);

        auto vm = glm::lookAt(Position, point, Up);
        Right = glm::transpose(vm)[0];

        auto xAngle = xoffset;
        auto yAngle = yoffset;

        auto viewDir = glm::vec3(-glm::transpose(vm)[2]);
        // if (glm::length(viewDir-Up) <= 0.1f)
        //     yAngle = 0;
        float cosAngle = glm::dot(viewDir, Up);
        if (cosAngle * sgn(yAngle) > 0.99f)
            yAngle = 0;


        auto m = glm::mat4(1.0f);
        // m = glm::rotate(m, glm::radians(xAngle), Up);
        // Position = (m * (pos - pivot)) + pivot;
        // m = glm::mat4(1.0f);
        // m = glm::rotate(m, glm::radians(yAngle), Right);
        // Position = (m * (pos - pivot)) + pivot;
        //m = glm::translate(m, glm::vec3(+2.0f));
        m = glm::rotate(m, glm::radians(xAngle), Up);
        m = glm::rotate(m, glm::radians(yAngle), Right);
        //m = glm::translate(m, glm::vec3(-2.0f));
        Position = (m * (pos - pivot)) + pivot;

        vm = glm::lookAt(Position, point, Up);
        Right = glm::transpose(vm)[0];

        Front = -glm::normalize(Position - point);
    }

    void Camera::ProcessMouseScroll(float yoffset) {
        Zoom -= (float) yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

    void Camera::updateCameraVectors() {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(
            glm::cross(Front,WorldUp)
        );  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }

    int Camera::sgn(double v) {
        if (v < 0) return -1;
        if (v > 0) return 1;
        return 0;
    }
}