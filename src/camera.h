//
// Created by kskun on 2022/5/17.
//

#ifndef MESH_VIEWER_CAMERA_H
#define MESH_VIEWER_CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    Camera() {}

    explicit Camera(glm::vec3 position, float fov = 60.0f);

    virtual ~Camera() = default;

    [[nodiscard]] glm::mat4 getViewMatrix() const;

    [[nodiscard]] float getFOV() const {
        return fov;
    }

    [[nodiscard]] glm::vec3 getPosition() const {
        return position;
    }

    virtual void handleMouseInput(float x, float y, bool pressed);

    virtual void handleKeyboardInput(int key, float deltaTime);

    virtual void handleScrollInput(float y);

protected:
    glm::vec3 position,
            front = {0.0f, 0.0f, -1.0f},
            up = {0.0f, 1.0f, 0.0f},
            right = {1.0f, 0.0f, 0.0f};
    float yaw = -90.0f, pitch = 0.0f, fov;

    bool firstMouseInput = true;
    float lastMouse[2];
};

class ModelRotationCamera : public Camera {
public:
    ModelRotationCamera() = default;

    explicit ModelRotationCamera(glm::vec3 center = {0.0f, 0.0f, 0.0f},
                                 float distance = 10.0f) :
            Camera(center - glm::vec3(0.0f, 0.0f, -distance), 60.0f),
            center(center), distance(distance) {}

    ~ModelRotationCamera() override = default;

    void handleMouseInput(float x, float y, bool pressed) override;

    void handleKeyboardInput(int key, float deltaTime) override;

    void handleScrollInput(float y) override;

protected:
    glm::vec3 center;
    float distance;
};

#endif //MESH_VIEWER_CAMERA_H
