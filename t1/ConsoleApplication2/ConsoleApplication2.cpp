// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <gl\glew.h>


#include <gl\glut.h>

#include<windows.h>


#include <math.h>

#include <iostream>


#include <stdio.h>



#include <time.h>

//#include <glm/glm.hpp>

//#include <glm/vec3.hpp> // glm::vec3
//#include <glm/vec4.hpp> // glm::vec4
//#include <glm/mat4x4.hpp> // glm::mat4

#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/constants.hpp> // glm::pi

//#include "vgl.h"  
#include "LoadShaders.h"  



#pragma comment(lib,"glew32d.lib")



enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];

const GLuint NumVertices = 6;
GLuint program;

void Initialize()
{

	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	GLfloat  vertices[NumVertices][2] = {
		{ -0.90, -0.90 },  // Triangle 1  
		{ 0.85, -0.90 },
		{ -0.90, 0.85 },
		{ 0.90, -0.85 },  // Triangle 2  
		{ 0.90, 0.90 },
		{ -0.85, 0.90 }
	};

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 然后使用了必需的vertex和fragment shaders  
	ShaderInfo  shaders[] = {
		{ GL_VERTEX_SHADER, "triangle.vert" },
		{ GL_FRAGMENT_SHADER, "triangle.frag" },
		{ GL_NONE, NULL }
	};

	// LoadShaders()是我们自定义(这里没有给出)的一个函数,  
	// 用于简化为GPU准备shaders的过程,后面会详细讲述  
	program = LoadShaders(shaders);
	glUseProgram(program);
	// 最后这部分我们成为shader plumbing,  
	// 我们把需要的数据和shader程序中的变量关联在一起,后面会详细讲述  


#define  BUFFER_OFFSET(offset) ((void *)(offset))
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
}

glm::mat4 mvp;
void glmFun()
{
	float _w = 1024;
	float _h = 768;
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)_w / (float)_h, 0.1f, 100.0f);

	
	
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around

	//mvp = glm::mat4(1.0f);

	GLuint MatrixID = glGetUniformLocation(program, "MVP");

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(VAOs[Triangles]);

	GLuint index = glGetUniformLocation(program,"InnerColor");
	if (index >= 0)
	{
		glUniform4f(index, 1.0f, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		printf("glUniform4f index:%d",index);
	}






	glDrawArrays(GL_TRIANGLES,0, NumVertices);
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	//glutInitContextVersion(3, 3);
	//glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(argv[0]);

	glewExperimental = TRUE;
	if (glewInit())
	{
		std::cerr << "Unable to initialize GLEW... Exiting..." << std::endl;
		std::exit(EXIT_FAILURE);
	}

	Initialize();
	glmFun();
	glutDisplayFunc(display);
	//glutIdleFunc(myIdle);
	glutMainLoop();
}

