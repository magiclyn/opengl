#pragma once
#include <gl/glew.h>
#include <gl/glut.h>
#include <iostream>
using namespace std;
typedef struct {
	GLenum	   type;
	const char*  filename;
	GLuint	   shader;
} ShaderInfo;
GLuint LoadShaders(ShaderInfo*);