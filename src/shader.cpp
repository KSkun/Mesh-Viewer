//
// Created by kskun on 2022/5/14.
//

#include "shader.h"

#include <glm/gtc/matrix_inverse.hpp>

Shader::Shader(const std::string &path, GLenum type) {
    if (!std::filesystem::exists(path)) {
        PLOG_FATAL << "Shader Compile Error: file not found";
        std::throw_with_nested("file not found");
    }
    std::ifstream f(path);
    std::stringstream ss;
    ss << f.rdbuf();
    auto source = ss.str();
    const GLchar *sourceData = source.data();
    const GLint sourceLength = source.size();
    glShaderType = type;
    glShader = glCreateShader(glShaderType);
    glShaderSource(glShader, 1, &sourceData, &sourceLength);
    glCompileShader(glShader);
    GLint status;
    glGetShaderiv(glShader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        char infoLog[512];
        glGetShaderInfoLog(glShader, 512, nullptr, infoLog);
        PLOG_FATAL << "Shader Compile Error: " << infoLog;
        std::throw_with_nested(infoLog);
    }
}

Shader::~Shader() {
    glDeleteShader(glShader);
    GLint status;
    glGetShaderiv(glShader, GL_DELETE_STATUS, &status);
    if (status == GL_FALSE) {
        char infoLog[512];
        glGetShaderInfoLog(glShader, 512, nullptr, infoLog);
        PLOG_FATAL << "Shader Delete Error: " << infoLog;
        std::throw_with_nested(infoLog);
    }
}

ShaderProgram::ShaderProgram(const Shader &vertex, const Shader &fragment) {
    if (vertex.glShaderType != GL_VERTEX_SHADER) {
        PLOG_FATAL << "Shader Type Error: " + std::to_string(vertex.glShader) + " is not a vertex shader";
        std::throw_with_nested(std::to_string(vertex.glShader) + " is not a vertex shader");
    }
    if (fragment.glShaderType != GL_FRAGMENT_SHADER) {
        PLOG_FATAL << "Shader Type Error: " + std::to_string(fragment.glShader) + " is not a fragment shader";
        std::throw_with_nested(std::to_string(fragment.glShader) + " is not a fragment shader");
    }
    glProgram = glCreateProgram();
    glAttachShader(glProgram, vertex.glShader);
    glAttachShader(glProgram, fragment.glShader);
    glLinkProgram(glProgram);
    GLint status;
    glGetProgramiv(glProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        char infoLog[512];
        glGetProgramInfoLog(glProgram, 512, nullptr, infoLog);
        PLOG_FATAL << "Program Link Error: " << infoLog;
        std::throw_with_nested(infoLog);
    }
}

ShaderProgram::ShaderProgram(const std::string &vertexPath, const std::string &fragmentPath) :
        ShaderProgram(Shader(vertexPath, GL_VERTEX_SHADER),
                      Shader(fragmentPath, GL_FRAGMENT_SHADER)) {}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(glProgram);
    GLint status;
    glGetProgramiv(glProgram, GL_DELETE_STATUS, &status);
    if (status == GL_FALSE) {
        char infoLog[512];
        glGetProgramInfoLog(glProgram, 512, nullptr, infoLog);
        PLOG_FATAL << "Program Delete Error: " << infoLog;
        std::throw_with_nested(infoLog);
    }
}

void ShaderProgram::use() const {
    glUseProgram(glProgram);
}

void ShaderProgram::setMVPMatrices(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection) {
    setMat4("model", model);
    setMat4("view", view);
    setMat4("projection", projection);

    // calculate normal transformation
    glm::mat3 norm(model);
    norm = glm::inverse(norm);
    norm = glm::transpose(norm);
    setMat3("norm", norm);
}
