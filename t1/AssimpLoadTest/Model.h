#ifndef _Model_H_
#define _Model_H_

#include <string.h>
#include <vector>
#include <gl/glew.h>
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// Other Libs
// 引入SOIL库
#include <SOIL/SOIL.h>

#pragma comment(lib,"Assimp.lib")

using namespace std;

class Model
{
public:
	/*  成员函数   */
	Model(GLchar* path)
	{
		this->loadModel(path);
	}

	Model()
	{
	}
	void Draw(Shader shader);//

	void loadModel(string path);
private:
	/*  模型数据  */
	vector<Mesh> meshes;
	string directory;

	/*  私有成员函数   */
	
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

	GLint TextureFromFile(const char* path, string directory)
	{
		//Generate texture ID and load texture data 
		string filename = string(path);
		filename = directory + '/' + filename;
		GLuint textureID;
		glGenTextures(1, &textureID);
		int width, height;
		const char* fileName2 = filename.c_str(); 
		int channels = 0;
		unsigned char* image = SOIL_load_image(fileName2, &width, &height, &channels, SOIL_LOAD_RGB);
		// Assign texture to ID
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		// Parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		SOIL_free_image_data(image);
		return textureID;
	}
};



#endif // _Model_H
