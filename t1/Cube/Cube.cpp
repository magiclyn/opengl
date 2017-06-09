// Cube.cpp : 定义控制台应用程序的入口点。
//

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
#include <SOIL/SOIL.h>

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

#pragma comment(lib,"SOIL.lib")



// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, -1.0f, // triangle 1 : begin
	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f, -1.0f, // triangle 2 : begin
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f, // triangle 2 : end
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f
};

// One color for each vertex. They were generated randomly.
static const GLfloat g_color_buffer_data[] = {
	0.583f, 0.771f, 0.014f,
	0.609f, 0.115f, 0.436f,
	0.327f, 0.483f, 0.844f,
	0.822f, 0.569f, 0.201f,
	0.435f, 0.602f, 0.223f,
	0.310f, 0.747f, 0.185f,
	0.597f, 0.770f, 0.761f,
	0.559f, 0.436f, 0.730f,
	0.359f, 0.583f, 0.152f,
	0.483f, 0.596f, 0.789f,
	0.559f, 0.861f, 0.639f,
	0.195f, 0.548f, 0.859f,
	0.014f, 0.184f, 0.576f,
	0.771f, 0.328f, 0.970f,
	0.406f, 0.615f, 0.116f,
	0.676f, 0.977f, 0.133f,
	0.971f, 0.572f, 0.833f,
	0.140f, 0.616f, 0.489f,
	0.997f, 0.513f, 0.064f,
	0.945f, 0.719f, 0.592f,
	0.543f, 0.021f, 0.978f,
	0.279f, 0.317f, 0.505f,
	0.167f, 0.620f, 0.077f,
	0.347f, 0.857f, 0.137f,
	0.055f, 0.953f, 0.042f,
	0.714f, 0.505f, 0.345f,
	0.783f, 0.290f, 0.734f,
	0.722f, 0.645f, 0.174f,
	0.302f, 0.455f, 0.848f,
	0.225f, 0.587f, 0.040f,
	0.517f, 0.713f, 0.338f,
	0.053f, 0.959f, 0.120f,
	0.393f, 0.621f, 0.362f,
	0.673f, 0.211f, 0.457f,
	0.820f, 0.883f, 0.371f,
	0.982f, 0.099f, 0.879f
};

static const GLfloat g_uv_buffer_data[] = {
	0.000059f, 1.0f - 0.000004f,
	0.000103f, 1.0f - 0.336048f,
	0.335973f, 1.0f - 0.335903f,
	1.000023f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.336024f, 1.0f - 0.671877f,
	0.667969f, 1.0f - 0.671889f,
	1.000023f, 1.0f - 0.000013f,
	0.668104f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.000059f, 1.0f - 0.000004f,
	0.335973f, 1.0f - 0.335903f,
	0.336098f, 1.0f - 0.000071f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.336024f, 1.0f - 0.671877f,
	1.000004f, 1.0f - 0.671847f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.668104f, 1.0f - 0.000013f,
	0.335973f, 1.0f - 0.335903f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.668104f, 1.0f - 0.000013f,
	0.336098f, 1.0f - 0.000071f,
	0.000103f, 1.0f - 0.336048f,
	0.000004f, 1.0f - 0.671870f,
	0.336024f, 1.0f - 0.671877f,
	0.000103f, 1.0f - 0.336048f,
	0.336024f, 1.0f - 0.671877f,
	0.335973f, 1.0f - 0.335903f,
	0.667969f, 1.0f - 0.671889f,
	1.000004f, 1.0f - 0.671847f,
	0.667979f, 1.0f - 0.335851f
};

unsigned int LoadTex(string Image)
{
	unsigned int Texture;

	//FILE* img = NULL;
	////img = fopen(Image.c_str(), "rb");

	//img = fopen(Image.c_str(), "rb");
	//if (!img)
	//{
	//	printf("Image could not be openedn");
	//	return 0;
	//}

	//unsigned long bWidth = 0;
	//unsigned long bHeight = 0;
	//DWORD size = 0;

	//fseek(img, 18, SEEK_SET);
	//fread(&bWidth, 4, 1, img);
	//fread(&bHeight, 4, 1, img);
	//fseek(img, 0, SEEK_END);
	//size = ftell(img) - 54;

	//unsigned char *data = (unsigned char*)malloc(size);

	//fseek(img, 54, SEEK_SET);    // image data
	//fread(data, size, 1, img);

	//fclose(img);

	int bWidth, bHeight;
	const char* fileName2 = Image.c_str();
	int channels = 1;


	unsigned char *data = SOIL_load_image(fileName2, &bWidth, &bHeight, &channels, SOIL_LOAD_RGB);



	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bWidth, bHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bWidth, bHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	if (data)
		free(data);

	//glGenerateMipmap(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, 0);

	return Texture;
}

GLuint vertexbuffer;

GLuint colorbuffer;

GLuint uvbuffer;

GLuint allbuffer;

GLuint vaovertex;

//GLuint vaocolor;

GLuint program;

GLuint texture;
GLuint texture2;

#define  BUFFER_OFFSET(offset) ((void *)(offset))

#define MY_PRINTF_SIMPLE
void Initialize()
{

	glGenVertexArrays(1, &vaovertex);
	glBindVertexArray(vaovertex);


#ifdef MY_PRINTF_SIMPLE

	glGenBuffers(1, &allbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, allbuffer);

	glBufferData(GL_ARRAY_BUFFER,sizeof(g_vertex_buffer_data)+sizeof(g_color_buffer_data)+ sizeof(g_uv_buffer_data),NULL,GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(g_vertex_buffer_data), g_vertex_buffer_data);
	glBufferSubData(GL_ARRAY_BUFFER,sizeof(g_vertex_buffer_data),sizeof(g_color_buffer_data), g_color_buffer_data);
	glBufferSubData(GL_ARRAY_BUFFER,sizeof(g_vertex_buffer_data)+sizeof(g_color_buffer_data),sizeof(g_uv_buffer_data), g_uv_buffer_data);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);


	glBindBuffer(GL_ARRAY_BUFFER, allbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glBindBuffer(GL_ARRAY_BUFFER, allbuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(g_vertex_buffer_data)));
	glBindBuffer(GL_ARRAY_BUFFER, allbuffer);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(g_vertex_buffer_data)+sizeof(g_color_buffer_data)));

#endif

#ifdef MY_PRINTF_SIMPLE2
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),NULL , GL_STATIC_DRAW); //g_vertex_buffer_data
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(g_vertex_buffer_data), g_vertex_buffer_data);

	//void * ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
	//memcpy(ptr, g_vertex_buffer_data, sizeof(g_vertex_buffer_data));
	//glUnmapBuffer(GL_ARRAY_BUFFER);

	glEnableVertexAttribArray(0);
	
	


	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);


	
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	
	glEnableVertexAttribArray(2);



	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

#endif

	texture = LoadTex("Rabbit_D.tga");     // load the texture 1.bmp
	texture2 = LoadTex("1.bmp");     // load the texture 
	//glBindTexture(GL_TEXTURE_2D, 0);
	//glBindSampler(texture, GL_TEXTURE0);




	ShaderInfo  shaders[] = {
		{ GL_VERTEX_SHADER, "cube.vert" },
		{ GL_FRAGMENT_SHADER, "cube.frag" },
		{ GL_NONE, NULL }
	};

	program = LoadShaders(shaders);
	glUseProgram(program);

	glEnable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	GLuint samplerID = glGetUniformLocation(program, "myTextureSampler");

	printf("%d",samplerID);

	glUniform1i(samplerID, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	GLuint samplerID2 = glGetUniformLocation(program, "myTextureSampler2");

	printf("%d", samplerID2);

	glUniform1i(samplerID2, 1);

	

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);
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


	//mvp = glm::mat4(1);
	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(0.0, 2.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glBindVertexArray(vaovertex);
	

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture);


	glDrawArrays(GL_TRIANGLES, 0, 6*6);
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
	printf("OpenGL version supported by this platform (%s): \n", \
		glGetString(GL_VERSION));

	Initialize();
	glmFun();
	glutDisplayFunc(display);
	//glutIdleFunc(myIdle);
	glutMainLoop();
}

