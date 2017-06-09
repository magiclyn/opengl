//#include "stdafx.h"
//
//
//// Std. Includes
//#include <string>
//
//// GLEW
//
//#include <gl/glew.h>
//
//// GLFW
//#include <GLFW/glfw3.h>
//
//// GL includes
//#include "Shader.h"
//#include "Camera.h"
//#include "Model.h"
//
//// GLM Mathemtics
//#include <glm/glm.hpp>
//
//#include <glm/gtc/type_ptr.hpp>
//
//
//
//#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
//#include <glm/gtc/constants.hpp> // glm::pi
//
//
//// Other Libs
//// 引入SOIL库
//#include <SOIL/SOIL.h>
//
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//
//
//#pragma comment (lib, "opengl32.lib")
//#pragma comment(lib,"glfw3.lib")
//#pragma comment(lib,"glew32d.lib")
//#pragma comment(lib,"assimp.lib")
//
//// Properties
//GLuint screenWidth = 800, screenHeight = 600;
//
//// Function prototypes
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void Do_Movement();
//
//// Camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//bool keys[1024];
//GLfloat lastX = 400, lastY = 300;
//bool firstMouse = true;
//
//GLfloat deltaTime = 0.0f;
//GLfloat lastFrame = 0.0f;
//
//// The MAIN function, from here we start our application and run our Game loop
//int main()
//{
//	// Init GLFW
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", nullptr, nullptr); // Windowed
//	glfwMakeContextCurrent(window);
//
//	// Set the required callback functions
//	glfwSetKeyCallback(window, key_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	// Options
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	// Initialize GLEW to setup the OpenGL Function pointers
//	glewExperimental = GL_TRUE;
//	glewInit();
//
//	// Define the viewport dimensions
//	glViewport(0, 0, screenWidth, screenHeight);
//
//	// Setup some OpenGL options
//	glEnable(GL_DEPTH_TEST);
//
//	// Setup and compile our shaders
//	//Shader shader("cube.vert", "cube.frag");
//
//	// Load models
//	Model ourModel("../../resources/models/cube/cube.obj");
//
//	// Draw in wireframe
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//	// Game loop
//	while (!glfwWindowShouldClose(window))
//	{
//		// Set frame time
//		GLfloat currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		// Check and call events
//		glfwPollEvents();
//		Do_Movement();
//
//		// Clear the colorbuffer
//		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		//shader.use();   // <-- Don't forget this one!
//		// Transformation matrices
//		//glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
//		//glm::mat4 view = camera.getViewMatrix();
//		//glUniformMatrix4fv(glGetUniformLocation(shader.programId, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//		//glUniformMatrix4fv(glGetUniformLocation(shader.programId, "view"), 1, GL_FALSE, glm::value_ptr(view));
//
//		// Draw the loaded model
//		//glm::mat4 model;
//		//model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
//		//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
//		//glUniformMatrix4fv(glGetUniformLocation(shader.programId, "model"), 1, GL_FALSE, glm::value_ptr(model));
//		ourModel.Draw();
//
//		// Swap the buffers
//		glfwSwapBuffers(window);
//	}
//
//	glfwTerminate();
//	return 0;
//}
//
//#pragma region "User input"
//
//// Moves/alters the camera positions based on user input
//void Do_Movement()
//{
//	// Camera controls
//	if (keys[GLFW_KEY_W])
//		camera.handleKeyPress(FORWARD, deltaTime);
//	if (keys[GLFW_KEY_S])
//		camera.handleKeyPress(BACKWARD, deltaTime);
//	if (keys[GLFW_KEY_A])
//		camera.handleKeyPress(LEFT, deltaTime);
//	if (keys[GLFW_KEY_D])
//		camera.handleKeyPress(RIGHT, deltaTime);
//}
//
//// Is called whenever a key is pressed/released via GLFW
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GL_TRUE);
//
//	if (action == GLFW_PRESS)
//		keys[key] = true;
//	else if (action == GLFW_RELEASE)
//		keys[key] = false;
//}
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	GLfloat xoffset = xpos - lastX;
//	GLfloat yoffset = lastY - ypos;
//
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.handleMouseMove(xoffset, yoffset);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.handleMouseScroll(yoffset);
//}
//
//#pragma endregion


















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

#include <string>

#include <time.h>

//#include <glm/glm.hpp>

//#include <glm/vec3.hpp> // glm::vec3
//#include <glm/vec4.hpp> // glm::vec4
//#include <glm/mat4x4.hpp> // glm::mat4

#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/constants.hpp> // glm::pi

//#include "vgl.h"  
//#include "LoadShaders.h"  

#include "Model.h"

using namespace  std;

#pragma comment(lib,"glew32d.lib")



unsigned int LoadTex(string Image)
{
	unsigned int Texture;

	FILE* img = NULL;
	//img = fopen(Image.c_str(), "rb");

	img = fopen(Image.c_str(), "rb");
	if (!img)
	{
		printf("Image could not be openedn");
		return 0;
	}

	unsigned long bWidth = 0;
	unsigned long bHeight = 0;
	DWORD size = 0;

	fseek(img, 18, SEEK_SET);
	fread(&bWidth, 4, 1, img);
	fread(&bHeight, 4, 1, img);
	fseek(img, 0, SEEK_END);
	size = ftell(img) - 54;

	unsigned char *data = (unsigned char*)malloc(size);

	fseek(img, 54, SEEK_SET);    // image data
	fread(data, size, 1, img);

	fclose(img);

	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bWidth, bHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bWidth, bHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

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

//GLuint program;

GLuint texture;

#define  BUFFER_OFFSET(offset) ((void *)(offset))

#define MY_PRINTF_SIMPLE

Model ourModel;
Shader shader;
void Initialize()
{

	shader.Load("cube.vert", "cube.frag");

	ourModel.loadModel("../../resources/models/Rabbit/Rabbit.obj");

	shader.use();
	//glGenVertexArrays(1, &vaovertex);
	//glBindVertexArray(vaovertex);


#ifdef MY_PRINTF_SIMPLE2

	glGenBuffers(1, &allbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, allbuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data)+sizeof(g_color_buffer_data)+sizeof(g_uv_buffer_data), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(g_vertex_buffer_data), g_vertex_buffer_data);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), sizeof(g_color_buffer_data), g_color_buffer_data);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data)+sizeof(g_color_buffer_data), sizeof(g_uv_buffer_data), g_uv_buffer_data);

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), NULL, GL_STATIC_DRAW); //g_vertex_buffer_data
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

	//texture = LoadTex("1.bmp");     // load the texture
	//glBindTexture(GL_TEXTURE_2D, 0);
	//glBindSampler(texture, GL_TEXTURE0);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//glUniform1i(glGetUniformLocation(shader.programId, "tex"), 0);

	//ShaderInfo  shaders[] = {
	//	{ GL_VERTEX_SHADER, "cube.vert" },
	//	{ GL_FRAGMENT_SHADER, "cube.frag" },
	//	{ GL_NONE, NULL }
	//};

	//program = LoadShaders(shaders);
	//glUseProgram(program);

	//glEnable(GL_TEXTURE_2D);
	//GLuint samplerID = glGetUniformLocation(program, "myTextureSampler");

	//printf("%d", samplerID);

	//glUniform1i(samplerID, 0);

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

	GLuint MatrixID = glGetUniformLocation(shader.programId, "MVP");

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//glBindVertexArray(vaovertex);

	ourModel.Draw(shader);
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture);


	//glDrawArrays(GL_TRIANGLES, 0, 6 * 6);
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

