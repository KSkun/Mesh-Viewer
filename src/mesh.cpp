//
// Created by kskun on 2022/5/14.
//

#include "mesh.h"

#include <OBJ_Loader.h>

Mesh::Mesh(const objl::Mesh &mesh, const std::string &objDir, const ShaderProgram &program) :
        indexSize(mesh.Indices.size()),
        material(program, {Texture2D(objDir + "/" + mesh.MeshMaterial.map_Kd)}) {
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
    material.use();
    glBindVertexArray(glVAO);
    glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Model::Model(const std::string &path, const ShaderProgram &program) {
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
    for (const auto &_mesh: loader->LoadedMeshes) {
        meshes.push_back(new Mesh(_mesh, objDir, program));
    }
}

Model::~Model() {
    delete loader;
    for (const auto mesh : meshes) {
        delete mesh;
    }
}

void Model::draw() const {
    for (const auto &mesh: meshes) {
        mesh->draw();
    }
}
