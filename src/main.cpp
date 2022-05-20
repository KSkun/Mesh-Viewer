#include <iostream>

#include <windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>

#include "shader.h"
#include "mesh.h"
#include "camera.h"

int width = 1600, height = 900;
float lastTime;
Camera *camera = nullptr;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void cursor_position_callback(GLFWwindow *window, double x, double y);

void scroll_callback(GLFWwindow* window, double x, double y);

void handle_keyboard(GLFWwindow* window, float deltaTime);

int main() {
    plog::init(plog::warning);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // create window
    GLFWwindow *window = glfwCreateWindow(width, height, "Mesh Viewer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // init glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, scroll_callback);

    ShaderProgram program("../src/shader/common.vert", "../src/shader/phong.frag");
    Model lumine("../resource/lumine/Lumine.obj", &program);
    camera = new ModelRotationCamera({0.0f, 10.0f, 0.0f}, 20.0f);
    lastTime = glfwGetTime();

    glm::vec3 lightPos(0.0f, 10.0f, 5.0f),
            lightColor(3.0f, 3.0f, 1.0f),
            lightAmbient(1.0f, 1.0f, 1.0f);

    glViewport(0, 0, width, height);
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float nowTime = glfwGetTime();
        float deltaTime = nowTime - lastTime;
        lastTime = nowTime;
        handle_keyboard(window, deltaTime);

        glm::mat4 model = glm::identity<glm::mat4>();
        glm::mat4 view = camera->getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera->getFOV()),
                                                (float) width / height, 0.1f, 100.0f);

        program.setMVPMatrices(model, view, projection);
        program.setVec3("eyePos", camera->getPosition());
        program.setVec3("light.position", lightPos);
        program.setVec3("light.ambient", lightAmbient);
        program.setVec3("light.diffuse", lightColor);
        program.setVec3("light.specular", lightColor);
        lumine.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete camera;
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    ::width = width;
    ::height = height;
    glViewport(0, 0, width, height);
}

void cursor_position_callback(GLFWwindow *window, double x, double y) {
    bool pressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    if (camera != nullptr) camera->handleMouseInput(x, y, pressed);
}

void scroll_callback(GLFWwindow* window, double x, double y) {
    if (camera != nullptr) camera->handleScrollInput(y);
}

void handle_keyboard(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        if (camera != nullptr) camera->handleKeyboardInput(GLFW_KEY_W, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if (camera != nullptr) camera->handleKeyboardInput(GLFW_KEY_A, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (camera != nullptr) camera->handleKeyboardInput(GLFW_KEY_S, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        if (camera != nullptr) camera->handleKeyboardInput(GLFW_KEY_D, deltaTime);
    }
}
