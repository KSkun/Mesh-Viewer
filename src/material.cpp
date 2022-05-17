//
// Created by kskun on 2022/5/14.
//

#include "material.h"

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

#include <utility>

Texture2D::Texture2D(const std::string &path) {
    if (!std::filesystem::exists(path)) {
        PLOG_FATAL << "Texture Load Error: file not found";
        std::throw_with_nested("file not found");
    }
    int channels;
    data = stbi_load(path.data(), &width, &height, &channels, 0);
    if (data == nullptr) {
        PLOG_FATAL << "Texture Load Error: unable to load image";
        std::throw_with_nested("unable to load image");
    }
    glGenTextures(1, &glTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, glTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture2D::~Texture2D() {
    if (data == nullptr) return;
    glDeleteTextures(1, &glTexture);
    stbi_image_free((void *) data);
}

void Texture2D::use(int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, glTexture);
}

Material::Material(ShaderProgram *program, std::vector<Texture2D *> textures) :
        program(program), textures(std::move(textures)) {}

void Material::use() const {
    program->use();
    for (int i = 0; i < textures.size(); i++) {
        textures[i]->use(i);
    }
}

PhongMaterial::PhongMaterial(ShaderProgram *program, std::vector<Texture2D *> textures,
                             int texDiffuse, int texSpecular, float shininess) :
        Material(program, std::move(textures)),
        texDiffuse(texDiffuse), texSpecular(texSpecular), shininess(shininess) {}

void PhongMaterial::use() const {
    program->setInt("material.diffuse", texDiffuse);
    program->setInt("material.specular", texSpecular);
    program->setFloat("material.shininess", shininess);
    Material::use();
}
