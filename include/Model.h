#pragma once
#ifndef MODEL_H     
#define  MODEL_H


#include<Mesh.h>
#include<assimp/material.h>
#include<string>
#include<iostream>
#include<assimp/importer.hpp>
#include<assimp/postprocess.h>
#include<assimp/scene.h>

class aiNode;
class aiScene;
class aiMesh;
class aiMaterials;
class Model {

public:
	/* Model data*/
	std::vector<Texture> textures_loaded_; // stores all the stored loaded
	std::vector<Mesh> meshes_;
	std::string directory_;
	bool gammaCorrection_;

	/* Functions*/
	//Constructor
	Model(std::string const &path, bool gamma = false);
	//Draws the model and thus all the meshes
	void Draw(const Shader& shader) const;
	static uint32_t GetTexture(const std::string pathtexture, bool flip);
private:
	/* Functions*/
	//Load a model with supported ASSIMP extensions from file and stores the result
	void loadModel(std::string const path);
	//Proccesses a node in a recursive mode. Proccesses each individual mesh
	void processNode(aiNode *node, const aiScene *scene);
	static uint32_t CreateTexture(const char* path, bool flip);

	Mesh processMesh(aiMesh *mesh, const aiScene *scene);

	//Checks all material texture of a given type and loads the textures if they are not loaded
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

};
#endif