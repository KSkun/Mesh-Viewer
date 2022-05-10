#include <iostream>
#include <fstream>
#include <sstream>

#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
};

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    GLFWwindow *window = glfwCreateWindow(800, 600, "Mesh Viewer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW windows" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // init vertex buffer
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // compile & link shaders
    std::ifstream ifVert("../src/shader/triangle.vert");
    std::stringstream ssVert;
    ssVert << ifVert.rdbuf();
    std::string strVert = ssVert.str();
    const char *bufVert = strVert.data();
    auto shaderVert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shaderVert, 1, &bufVert, nullptr);
    glCompileShader(shaderVert);
    std::ifstream ifFrag("../src/shader/triangle.frag");
    std::stringstream ssFrag;
    ssFrag << ifVert.rdbuf();
    std::string strFrag = ssFrag.str();
    const char *bufFrag = strFrag.data();
    auto shaderFrag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shaderFrag, 1, &bufFrag, nullptr);
    glCompileShader(shaderFrag);
    auto program = glCreateProgram();
    glAttachShader(program, shaderVert);
    glAttachShader(program, shaderFrag);
    glLinkProgram(program);
    glDeleteShader(shaderVert);
    glDeleteShader(shaderFrag);

    glViewport(0, 0, 800, 600);
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(program);

    glfwTerminate();
    return 0;
}
