//
// Created by kskun on 2022/5/14.
//

#include "mesh.h"

#include <OBJ_Loader.h>

Mesh::Mesh(const objl::Mesh &mesh, Material *material) :
        indexSize(mesh.Indices.size()), material(material) {
    vertices = new float[8 * mesh.Vertices.size()];
    indices = new unsigned int[mesh.Indices.size()];
    memcpy(vertices, mesh.Vertices.data(), 8 * sizeof(float) * mesh.Vertices.size());
    memcpy(indices, mesh.Indices.data(), sizeof(unsigned int) * mesh.Indices.size());

    glGenVertexArrays(1, &glVAO);
    glGenBuffers(1, &glVBO);
    glGenBuffers(1, &glEBO);

    glBindVertexArray(glVAO);
    glBindBuffer(GL_ARRAY_BUFFER, glVBO);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float) * mesh.Vertices.size(), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.Indices.size(), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0); // position
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float))); // normal
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float))); // texcoord

    glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &glVBO);
    glDeleteBuffers(1, &glEBO);
    glDeleteVertexArrays(1, &glVAO);

    delete[] vertices;
    delete[] indices;
}

void Mesh::draw() const {
    material->use();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    glBindVertexArray(glVAO);
    glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Model::Model(const std::string &path, ShaderProgram *program) : program(program) {
    if (!std::filesystem::exists(path)) {
        PLOG_FATAL << "Model Load Error: file not found " + path;
        std::throw_with_nested("file not found " + path);
    }
    loader = new objl::Loader;
    if (!loader->LoadFile(path)) {
        PLOG_FATAL << "Model Load Error: unable to load model " + path;
        std::throw_with_nested("unable to load model " + path);
    }
    auto objDir = std::filesystem::path(path).parent_path().string();
    for (const auto &_material: loader->LoadedMaterials) {
        materials[_material.name] = new PhongMaterial(program, {loadTexture(objDir + "/" + _material.map_Kd)},
                                                      0, 0, _material.Ns);
    }
    for (const auto &_mesh: loader->LoadedMeshes) {
        meshes.push_back(new Mesh(_mesh, materials[_mesh.MeshMaterial.name]));
    }
}

Model::~Model() {
    delete loader;
    for (const auto mesh: meshes) {
        delete mesh;
    }
    for (const auto &material: materials) {
        delete material.second;
    }
    for (const auto &texture: textures) {
        delete texture.second;
    }
}

void Model::draw() const {
    for (const auto &mesh: meshes) {
        mesh->draw();
    }
}

Texture2D *Model::loadTexture(const std::string &path) {
    if (textures.contains(path)) return textures[path];
    return textures[path] = new Texture2D(path);
}
