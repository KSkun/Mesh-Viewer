//
// Created by kskun on 2022/5/14.
//

#ifndef MESH_VIEWER_MESH_H
#define MESH_VIEWER_MESH_H

#include <string>

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

    Mesh(const objl::Mesh &mesh, const std::string &objDir, const ShaderProgram &program);

    virtual ~Mesh();

    virtual void draw() const;

protected:
    int indexSize;
    float *vertices;
    unsigned int *indices;
    GLuint glVAO, glVBO, glEBO;
    Material material;
};

class Model {
public:
    Model() {}

    Model(const std::string &path, const ShaderProgram &program);

    virtual ~Model();

    virtual void draw() const;

protected:
    objl::Loader *loader;
    std::vector<Mesh *> meshes;
};

#endif //MESH_VIEWER_MESH_H
