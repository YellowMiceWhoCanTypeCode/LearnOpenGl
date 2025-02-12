#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <assimp/material.h>

class Object;
struct aiMaterial;
struct aiMesh;
struct aiScene;
struct aiNode;
class Material;
class Mesh;
class Shader;
class Texture;

class Model
{
public:
    // model data 
    std::vector<Texture*> textures_loaded; // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh*> meshes;
    std::string directory;
    bool gammaCorrection;

    Model(std::string const& path, bool gamma = false);

    // draws the model, and thus all its meshes
    void Draw(Shader* shader, Object* owner);

private:
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(std::string const& path);

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode* node, const aiScene* scene);

    Mesh* processMesh(aiMesh* mesh, const aiScene* scene);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    std::vector<Texture*> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};
