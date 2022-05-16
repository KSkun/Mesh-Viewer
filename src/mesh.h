//
// Created by kskun on 2022/5/14.
//

#ifndef MESH_VIEWER_MESH_H
#define MESH_VIEWER_MESH_H

#include <string>
#include <unordered_map>

#include <windows.h>
#include <glad/glad.h>

#include "material.h"

namespace objl {
    class Mesh;

    class Loader;
}

class Mesh {
public:
    Mesh() {}

    Mesh(const objl::Mesh &mesh, Material *material);

    virtual ~Mesh();

    virtual void draw() const;

protected:
    int indexSize;
    float *vertices;
    unsigned int *indices;
    GLuint glVAO, glVBO, glEBO;
    Material *material;
};

class Model {
public:
    Model() {}

    Model(const std::string &path, ShaderProgram *program);

    virtual ~Model();

    virtual void draw() const;

protected:
    Texture2D *loadTexture(const std::string &path);

    objl::Loader *loader = nullptr;
    std::vector<Mesh *> meshes;
    ShaderProgram *program = nullptr;
    std::unordered_map<std::string, Texture2D *> textures;
    std::unordered_map<std::string, Material *> materials;
};

#endif //MESH_VIEWER_MESH_H
