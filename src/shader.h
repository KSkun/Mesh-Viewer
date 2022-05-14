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

#include <plog/Log.h>

class Shader;

class ShaderProgram;

class Shader {
    friend ShaderProgram;
public:
    explicit Shader(const std::string &path, GLenum type);

    virtual ~Shader();

protected:
    GLuint glShader;
    GLenum glShaderType;
};

class ShaderProgram {
public:
    ShaderProgram(const Shader &vertex, const Shader &fragment);

    ShaderProgram(const std::string &vertexPath, const std::string &fragmentPath);

    virtual ~ShaderProgram();

    void use() const;

protected:
    GLuint glProgram;
};


#endif //MESH_VIEWER_SHADER_H
