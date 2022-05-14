//
// Created by kskun on 2022/5/14.
//

#ifndef MESH_VIEWER_MATERIAL_H
#define MESH_VIEWER_MATERIAL_H

#include "shader.h"

class Texture2D;

class Material;

class Texture2D {
    friend Material;
public:
    Texture2D() {}

    explicit Texture2D(const std::string &path);

    Texture2D(const char *data, int width, int height);

    virtual ~Texture2D();

    virtual void use(int unit) const;

protected:
    GLuint glTexture;
    int width, height;
};

class Material {
public:
    Material() {}

    Material(const ShaderProgram &program, std::vector<Texture2D> textures);

    virtual void use() const;

protected:
    ShaderProgram program;
    std::vector<Texture2D> textures;
};

#endif //MESH_VIEWER_MATERIAL_H
