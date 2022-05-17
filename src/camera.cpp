//
// Created by kskun on 2022/5/17.
//

#include "camera.h"

#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

static const float cameraMouseSpeed = 0.05f, cameraKeyboardSpeed = 1.0f, cameraScroolSpeed = 5.0f;

Camera::Camera(glm::vec3 position, float fov) :
    position(position), fov(fov) {}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

void Camera::handleMouseInput(float x, float y, bool pressed) {
    if (firstMouseInput || !pressed) {
        lastMouse[0] = x;
        lastMouse[1] = y;
        firstMouseInput = false;
        return;
    }

    float dx = x - lastMouse[0], dy = y - lastMouse[1];
    yaw -= dx * cameraMouseSpeed;
    pitch += dy * cameraMouseSpeed;
    pitch = std::max(std::min(pitch, 90.0f), -90.0f); // clamp to [-90.0, 90.0] degree

    front = glm::normalize(glm::vec3(
            std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch)),
            std::sin(glm::radians(pitch)),
            std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch))
    ));
    right = glm::cross(front, up);

    lastMouse[0] = x;
    lastMouse[1] = y;
}

void Camera::handleKeyboardInput(int key) {
    if (key == GLFW_KEY_W) {
        position += front * cameraKeyboardSpeed;
    } else if (key == GLFW_KEY_S) {
        position -= front * cameraKeyboardSpeed;
    } else if (key == GLFW_KEY_A) {
        position -= right * cameraKeyboardSpeed;
    } else if (key == GLFW_KEY_D) {
        position += right * cameraKeyboardSpeed;
    }
}

void Camera::handleScrollInput(float y) {
    fov -= y * cameraScroolSpeed;
    fov = std::max(std::min(fov, 80.0f), 1.0f);
}
