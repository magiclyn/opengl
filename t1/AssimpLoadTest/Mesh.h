#ifndef _MESH_H_
#define  _MESH_H_

#include <string.h>
#include <vector>
#include <gl/glew.h>

// “˝»ÎGLMø‚
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include "shader.h"
#include <sstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#pragma comment (lib, "opengl32.lib")
#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"glew32d.lib")
#pragma comment(lib,"SOIL.lib")

using namespace std;

struct  Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	GLuint id;
	string type;
	aiString path;
};

class Mesh
{
public:
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> texture);
	void Draw(Shader shader);

private:
	GLuint VAO, VBO, EBO;
	void setupMesh();
};

#endif