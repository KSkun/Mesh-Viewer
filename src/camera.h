//
// Created by kskun on 2022/5/17.
//

#ifndef MESH_VIEWER_CAMERA_H
#define MESH_VIEWER_CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    Camera() {}

    Camera(glm::vec3 position, float fov = 60.0f);

    [[nodiscard]] glm::mat4 getViewMatrix() const;

    [[nodiscard]] float getFOV() const {
        return fov;
    }

    [[nodiscard]] glm::vec3 getPosition() const {
        return position;
    }

    void handleMouseInput(float x, float y, bool pressed);

    void handleKeyboardInput(int key, float deltaTime);

    void handleScrollInput(float y);

protected:
    glm::vec3 position,
            front = {0.0f, 0.0f, -1.0f},
            up = {0.0f, 1.0f, 0.0f},
            right = {1.0f, 0.0f, 0.0f};
    float yaw = -90.0f, pitch = 0.0f, fov;

    bool firstMouseInput = true;
    float lastMouse[2];
};

#endif //MESH_VIEWER_CAMERA_H
