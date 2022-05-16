//
// Created by kskun on 2022/5/14.
//

#ifndef MESH_VIEWER_SHADER_H
#define MESH_VIEWER_SHADER_H

#include <string>
#include <fstream>
#include <filesystem>

#include <windows.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <plog/Log.h>

class Shader;

class ShaderProgram;

class Shader {
    friend ShaderProgram;
public:
    Shader() {}

    explicit Shader(const std::string &path, GLenum type);

    virtual ~Shader();

protected:
    GLuint glShader;
    GLenum glShaderType;
};

class ShaderProgram {
public:
    ShaderProgram() {}

    ShaderProgram(const Shader &vertex, const Shader &fragment);

    ShaderProgram(const std::string &vertexPath, const std::string &fragmentPath);

    virtual ~ShaderProgram();

    void use() const;

    void setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(glProgram, name.data()), value);
    }

    void setMat4(const std::string &name, const glm::mat4 &mat) const {
        glUniformMatrix4fv(glGetUniformLocation(glProgram, name.data()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat3(const std::string &name, const glm::mat3 &mat) const {
        glUniformMatrix3fv(glGetUniformLocation(glProgram, name.data()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMVPMatrices(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection);

protected:
    GLuint glProgram;
};


#endif //MESH_VIEWER_SHADER_H
