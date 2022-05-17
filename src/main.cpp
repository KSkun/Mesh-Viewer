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

int width = 1600, height = 900;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // init glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    ShaderProgram program("../src/shader/common.vert", "../src/shader/phong.frag");
    Model lumine("../resource/lumine/Lumine.obj", &program);

    glm::vec3 eyePos(0.0f, 10.0f, 20.0f),
            lookatPos(0.0f, 10.0f, 0.0f);
    float fov = glm::radians(60.0f);

    glm::vec3 lightPos(0.0f, 10.0f, 5.0f),
            lightColor(1.0f, 1.0f, 1.0f),
            lightAmbient(1.0f, 1.0f, 1.0f);

    glViewport(0, 0, width, height);
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::identity<glm::mat4>();
        glm::mat4 view = glm::lookAt(eyePos, lookatPos, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 projection = glm::perspective(fov, (float) width / height, 0.1f, 100.0f);

        program.setMVPMatrices(model, view, projection);
        program.setVec3("eyePos", eyePos);
        program.setVec3("light.position", lightPos);
        program.setVec3("light.ambient", lightAmbient);
        program.setVec3("light.diffuse", lightColor);
        program.setVec3("light.specular", lightColor);
        lumine.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    ::width = width;
    ::height = height;
    glViewport(0, 0, width, height);
}
