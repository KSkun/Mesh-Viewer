#include <iostream>

#include <windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>

#include <OBJ_Loader.h>

#include "shader.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

int main() {
    plog::init(plog::warning);

    objl::Loader loader;
    loader.LoadFile("../resource/lumine/Lumine.obj");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    GLFWwindow *window = glfwCreateWindow(800, 600, "Mesh Viewer", nullptr, nullptr);
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

    // compile & link shaders
    ShaderProgram program("../src/shader/triangle.vert", "../src/shader/triangle.frag");

    glViewport(0, 0, 800, 600);
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
