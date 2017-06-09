#ifndef _MODEL_H_
#define _MODEL_H_

#include "shader.h"
#include <iostream>
#include <string.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>

using namespace std;
class Model
{
public:
	Model(GLchar* path)
	{
		this->loadModel(path);
	}
	~Model();

	void Draw(Shader shdaer);

private:
	vector<Mesh> meshes;
	string directory;

	/*  私有成员函数   */
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};
#endif

