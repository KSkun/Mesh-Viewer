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

    virtual ~Texture2D();

    virtual void use(int unit) const;

protected:
    const unsigned char *data = nullptr;
    GLuint glTexture;
    int width, height;
};

class Material {
public:
    Material() {}

    Material(ShaderProgram *program, std::vector<Texture2D *> textures);

    virtual void use() const;

protected:
    // don't delete them in dtor
    // Material is just a combination of program, textures and parameters
    // manage program & textures in models
    ShaderProgram *program = nullptr;
    std::vector<Texture2D *> textures;
};

class PhongMaterial : public Material {
public:
    PhongMaterial() {}

    PhongMaterial(ShaderProgram *program, std::vector<Texture2D *> textures, int texDiffuse, int texSpecular, float shininess);

    void use() const override;

protected:
    int texDiffuse, texSpecular;
    float shininess;
};

#endif //MESH_VIEWER_MATERIAL_H
