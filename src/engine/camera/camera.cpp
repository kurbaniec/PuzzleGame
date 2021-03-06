//
// Created by kurbaniec on 23.12.2021.
//

#include "camera.h"

namespace engine {

    Camera::Camera(
        glm::vec3 position, glm::vec3 up,
        float yaw, float pitch, float speed, float sensitivity, float zoom,
        Mode mode, glm::vec3 target
    ) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(speed),
        mouseSensitivity(sensitivity), zoom(zoom), mode(mode), target(target) {
        this->position = position;
        this->worldUp = up;
        this->yaw = yaw;
        this->pitch = pitch;
        if (mode == FREE) {
            updateCameraVectorsFree();
        } else if (mode == ORBIT) {
            updateCameraVectorsOrbit();
        }
    }

    Camera::Camera(
        float posX, float posY, float posZ,
        float upX, float upY, float upZ,
        float yaw, float pitch,
        Mode mode, glm::vec3 target
    ) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED),
        mouseSensitivity(SENSITIVITY), zoom(ZOOM), mode(mode), target(target) {
        this->position = glm::vec3(posX, posY, posZ);
        this->worldUp = glm::vec3(upX, upY, upZ);
        this->yaw = yaw;
        this->pitch = pitch;
        if (mode == FREE) {
            updateCameraVectorsFree();
        } else if (mode == ORBIT) {
            updateCameraVectorsOrbit();
        }
    }

    glm::mat4 Camera::getViewMatrix() const {
        return viewMatrix;
    }


    void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
        float velocity = movementSpeed * deltaTime;
        if (direction == FORWARD)
            position += front * velocity;
        if (direction == BACKWARD)
            position -= front * velocity;
        if (direction == LEFT)
            position -= right * velocity;
        if (direction == RIGHT)
            position += right * velocity;

        updateCameraVectors();
    }

    void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
        if (mode == FREE) {
            xoffset *= mouseSensitivity;
            yoffset *= mouseSensitivity;

            yaw += xoffset;
            pitch += yoffset;

            // make sure that when pitch is out of bounds, screen doesn't get flipped
            if (constrainPitch) {
                if (pitch > 89.0f)
                    pitch = 89.0f;
                if (pitch < -89.0f)
                    pitch = -89.0f;
            }

            // update Front, Right and Up Vectors using the updated Euler angles
            updateCameraVectorsFree();
        } else {
            // Orbit camera
            // See: https://asliceofrendering.com/camera/2019/11/30/ArcballCamera/
            auto xAngle = xoffset * mouseSensitivity;
            auto yAngle = yoffset * mouseSensitivity;

            float cosAngle = glm::dot(front, up);
            if (cosAngle * sgn(yAngle) > 0.99f)
                yAngle = 0;

            auto m = glm::mat4(1.0f);
            m = glm::rotate(m, glm::radians(xAngle), up);
            m = glm::rotate(m, glm::radians(yAngle), right);
            position = (m * (glm::vec4(position, 1.0f) - glm::vec4(target, 1.0f)))
                       + glm::vec4(target, 1.0f);

            updateCameraVectorsOrbit();
        }
    }

    void Camera::processMouseScroll(float yoffset) {
        zoom -= (float) yoffset;
        if (zoom < 1.0f)
            zoom = 1.0f;
        if (zoom > 45.0f)
            zoom = 45.0f;

        updateCameraVectors();
    }

    void Camera::updateCameraVectorsFree() {
        // calculate the new Front vector
        glm::vec3 frontTmp;
        frontTmp.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        frontTmp.y = sin(glm::radians(pitch));
        frontTmp.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(frontTmp);
        // also re-calculate the Right and Up vector
        right = glm::normalize(
            glm::cross(front, worldUp)
        );  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        up = glm::normalize(glm::cross(right, frontTmp));
        viewMatrix = glm::lookAt(position, position + front, up);
    }

    void Camera::updateCameraVectorsOrbit() {
        up = worldUp;
        //right = glm::transpose(viewMatrix)[0];
        front = -glm::normalize(position - target);
        right = glm::normalize(
            glm::cross(front, worldUp)
        );
        viewMatrix = glm::lookAt(position, target, up);
    }

    void Camera::updateCameraVectors() {
        if (mode == FREE) {
            updateCameraVectorsFree();
        } else if (mode == ORBIT) {
            updateCameraVectorsOrbit();
        }
    }

    void Camera::toggleMode() {
        if (mode == FREE) {
            mode = ORBIT;
            updateCameraVectorsOrbit();
        } else {
            mode = FREE;
            updateCameraVectorsFree();
        }
    }

    void Camera::setPosition(glm::vec3 newPosition) {
        position = newPosition;
        updateCameraVectors();
    }

    void Camera::setTarget(glm::vec3 newTarget) {
        target = newTarget;
        updateCameraVectors();
    }

    void Camera::setSpeed(float speed) {
        movementSpeed = speed;
    }

    void Camera::setSensitivity(float sensitivity) {
        mouseSensitivity = sensitivity;
    }

    glm::vec3 Camera::getPosition() const {
        return position;
    }

    glm::vec3 Camera::getTarget() const {
        return target;
    }

    float Camera::getZoom() const {
        return zoom;
    }

    Mode Camera::getMode() const {
        return mode;
    }

    float Camera::getSensitivity() const {
        return mouseSensitivity;
    }

    float Camera::getSpeed() const {
        return movementSpeed;
    }

    int Camera::sgn(double v) {
        if (v < 0) return -1;
        if (v > 0) return 1;
        return 0;
    }
}
