#include "stdafx.h"
#include <iostream>

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"

#pragma comment (lib, "opengl32.lib")
#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"glew32d.lib")

int main(int argc, _TCHAR* argv[])
{

	GLFWwindow* window;

	std::cout << "Swwwwwwwwwwwwwwwww" << std::endl;

	//if (!glfwInit())
	//{
	//	std::cout << "glfw init error " << std::endl;
	//}

	glfwInit();

	// 开启OpenGL 3.3 core profile
	std::cout << "Start OpenGL core profile version 3.3" << std::endl;

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	//window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	//if (!window)
	//{
	//	glfwTerminate();
	//	return -1;
	//}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(480, 320, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSize(window, 800, 600);

	glfwMakeContextCurrent(window);

	//glewExperimental = GL_TRUE; // 让glew获取所有拓展函数
	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		std::cout << "Error::GLEW glew version:" << glewGetString(GLEW_VERSION)
			<< " error string:" << glewGetErrorString(status) << std::endl;
		glfwTerminate();
		return -1;
	}

	Shader shader("scene.vertex", "scene.frag");

	//while (!glfwWindowShouldClose(window))
	//{
	//	glClear(GL_COLOR_BUFFER_BIT);
	//	/* Draw a triangle */
	//	glBegin(GL_TRIANGLES);

	//	glColor3f(1.0, 0.0, 0.0);    // Red
	//	glVertex3f(0.0, 1.0, 0.0);

	//	glColor3f(0.0, 1.0, 0.0);    // Green
	//	glVertex3f(-1.0, -1.0, 0.0);

	//	glColor3f(0.0, 0.0, 1.0);    // Blue
	//	glVertex3f(1.0, -1.0, 0.0);

	//	glEnd();

	//	/* Swap front and back buffers */
	//	glfwSwapBuffers(window);

	//	/* Poll for and process events */
	//	glfwPollEvents();

	//}
	//glfwTerminate();
	return 0;
}











