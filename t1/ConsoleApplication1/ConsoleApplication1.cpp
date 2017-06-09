// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <gl\glew.h>


#include <gl\glut.h>

#include<windows.h>


#include <math.h>

#include <iostream>


#include <stdio.h>



#include <time.h>

#include <glm/glm.hpp>

  
#pragma comment (lib, "opengl32.lib")
#pragma comment(lib,"glew32d.lib")




double CalFrequency()
{
	static int count;
	static double save;
	static clock_t last, current;
	double timegap;

	++count;
	if (count <= 50)
		return save;
	count = 0;
	last = current;
	current = clock();
	timegap = (current - last) / (double)CLK_TCK;
	save = 50.0 / timegap;
	return save;
}

const int n = 200;
const GLfloat R = 0.5f;
const GLfloat Pi = 3.1415926536f;
void myDisplay(void)
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	for (i = 0; i < n; ++i)
		glVertex2f(R*cos(2 * Pi / n*i), R*sin(2 * Pi / n*i));
	glEnd();


	glFlush();
}

void myDisplay1(void)
{
	double FPS = CalFrequency();
	printf("FPS = %f\n", FPS);

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 1.0f, 1.0f);
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	glFlush();
}

void myDisplay2(void)
{
	GLfloat a = 1 / (2 - 2 * cos(72 * Pi / 180));
	GLfloat bx = a * cos(18 * Pi / 180);
	GLfloat by = a * sin(18 * Pi / 180);
	GLfloat cy = -a * cos(18 * Pi / 180);
	GLfloat
		PointA[2] = { 0, a },
		PointB[2] = { bx, by },
		PointC[2] = { 0.5, cy },
		PointD[2] = { -0.5, cy },
		PointE[2] = { -bx, by };

	//glPointSize(7.5f);
	//glLineWidth(1.0F);
	//glEnable(GL_LINE_STIPPLE);

	//glLineStipple(2, 0x00ff);


	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	glFrontFace(GL_CCW);

	glClear(GL_COLOR_BUFFER_BIT);
	// 按照A->C->E->B->D->A的顺序，可以一笔将五角星画出
	//glBegin(GL_POLYGON);
	//glColor3f(0.0f, 1.0f, 1.0f);
	//glVertex2fv(PointA);
	//glVertex2fv(PointC);
	//glVertex2fv(PointE);
	//glVertex2fv(PointB);
	////glVertex2fv(PointD);
	//glEnd();


	glBegin(GL_POLYGON);               // 按逆时针绘制一个正方形，在左下方

	glVertex2f(-0.5f, -0.5f);

	glVertex2f(0.0f, -0.5f);

	glVertex2f(0.0f, 0.0f);

	glVertex2f(-0.5f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);               // 按顺时针绘制一个正方形，在右上方

	glVertex2f(0.0f, 0.0f);

	glVertex2f(0.0f, 0.5f);

	glVertex2f(0.5f, 0.5f);

	glVertex2f(0.5f, 0.0f);

	glEnd();

	glFlush();
}

const GLfloat factor = 0.1f;
void myDisplay3(void)
{
	GLfloat x;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);         // 以上两个点可以画x轴
	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);         // 以上两个点可以画y轴
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (x = -1.0f / factor; x < 1.0f / factor; x += 0.01f)
	{
		glVertex2f(x*factor, sin(x)*factor);
	}
	glEnd();
	glFlush();
}

void myDisplay4(void)
{
	int i;
	// glShadeModel(GL_FLAT);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);
	for (i = 0; i <= 8; ++i)
	{
		glColor3f(i & 0x04, i & 0x02, i & 0x01);
		glVertex2f(cos(i*Pi / 4), sin(i*Pi / 4));
	}
	glEnd();
	glFlush();
}



#define WIDTH 400
#define HEIGHT 400

static GLfloat angle = 0.0f;

void myDisplay5(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 创建透视效果视图
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// 定义太阳光源，它是一种白色的光源
	{
		GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
	}

	// 定义太阳的材质并绘制太阳
	{
		GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_emission[] = { 0.5f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_shininess = 0.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);

		glutSolidSphere(2.0, 40, 32);
	}

	// 定义地球的材质并绘制地球
	{
		GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat earth_mat_shininess = 30.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

		glRotatef(angle, 0.0f, -1.0f, 0.0f);
		glTranslatef(-5.0f, 0.0f, 0.0f);
		glutSolidSphere(2.0, 40, 32);
	}

	glutSwapBuffers();
}

void myDisplay6(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 创建透视效果视图
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	

	// 定义太阳光源，它是一种白色的光源
	{
		GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
	}

	// 定义太阳的材质并绘制太阳
	{
		GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_emission[] = { 0.5f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_shininess = 0.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);

		glutSolidSphere(2.0, 40, 32);
	}

	// 定义地球的材质并绘制地球
	{
		GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		GLfloat earth_mat_emission[] = { 0.1f, 0.0f, 0.0f, 1.0f };
		GLfloat earth_mat_shininess = 10.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

		glRotatef(angle, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 5.0f, 0.0f);
		glutSolidSphere(2.0, 40, 32);
	}

	glutSwapBuffers();
}

void myIdle(void)
{
	angle += 1.0f;
	if (angle >= 360.0f)
		angle = 0.0f;
	printf("angle = %f\n", angle);
	myDisplay6();
}


GLuint Buffer_ID;
const int BUFFER_NUMBER = 1;

GLuint VAO_ID;
GLuint VAO_NUMBER = 1;

const int VERTICES_NUMBER = 6;
const int vPosition = 0;

void Initialize()
{
     //---------------------准备数据-------------------------------
     GLfloat vertices[VERTICES_NUMBER][2] =
     {
         { -0.90, -0.90 },
         {  0.85, -0.90 },
         { -0.90, 0.85 },

         {  0.90, -0.85 },
         {  0.90, 0.90 },
         { -0.85, 0.90 }
     };

     // 生成缓存对象
     glGenBuffers(BUFFER_NUMBER, &Buffer_ID);

     // 绑定缓存对象
     glBindBuffer(GL_ARRAY_BUFFER, Buffer_ID);

     // 填入数据
     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

     //-------------------设置顶点数据属性------------------------------
     // 生成顶点数组对象
     glGenVertexArrays(VAO_NUMBER, &VAO_ID);

     // 绑定顶点数组对象
     glBindVertexArray(VAO_ID);

     // 设置顶点属性
     glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
	 glEnableVertexAttribArray(vPosition);
}

void display7()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(VAO_ID);
	glDrawArrays(GL_TRIANGLES, 0, VERTICES_NUMBER);

	glFlush();
}


//int main(int argc, char *argv[])
//{
//	
//	glutInit(&argc, argv);
//	//glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
//	//glutInitWindowPosition(100, 100);
//	//glutInitWindowSize(400, 400);
//	//glutCreateWindow("第一个OpenGL程序");
//
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
//	glutInitWindowPosition(200, 200);
//	glutInitWindowSize(WIDTH, HEIGHT);
//	glutCreateWindow("OpenGL光照演示");
//
//	glutDisplayFunc(&display7);
//	glutIdleFunc(&myIdle);
//	glutMainLoop();
//	//Sleep(2000);
//	return 0;
//}

static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
};


GLuint vertexbuff;
GLuint vao;

void Initialize2()
{
	

	glGenBuffers(1, &vertexbuff);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuff);

	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,(void*)0);
	glEnableVertexAttribArray(0);

}


GLuint fbo;
GLuint rendertarget;
GLuint g_depthbuffer;

int TEXTURE_WIDTH = 512;
int TEXTURE_HEIGHT = 512;

int SCREEN_WIDTH = 512;
int SCREEN_HEIGHT = 512;




// 初始化摄像机
//void SetupCamera(void)
//{
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	//gluPerspective(45, (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT, NEAR_PLANE, FAR_PLANE);
//	gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
//	gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
//
//	// 各种变换应该在GL_MODELVIEW模式下进行
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	// Z-buffer
//	glEnable(GL_DEPTH_TEST);
//	glDepthFunc(GL_LESS);
//
//	// 启用2D贴图
//	glEnable(GL_TEXTURE_2D);
//}
//
//// 初始化几何形体
//void SetupResource(void)
//{
//	// 创建纹理
//	glGenTextures(1, &rendertarget);
//	glBindTexture(GL_TEXTURE_2D, rendertarget);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	/*
//	// 创建深度缓冲区
//	glGenRenderbuffersEXT(1, &depthbuffer);
//	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthbuffer);
//	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, TEXTURE_WIDTH, TEXTURE_HEIGHT);
//	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
//	*/
//
//	// 创建FBO对象
//	glGenFramebuffers(1, &fbo);
//	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rendertarget, 0);
//	//glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthbuffer);
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER);
//	if (status != GL_FRAMEBUFFER_COMPLETE)
//	{
//
//	}
//}
//
//// 渲染到窗体
//void Render(void)
//{
//	// 绑定默认FBO（窗体帧缓冲区的ID是0）
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	glBindTexture(GL_TEXTURE_2D, rendertarget);
//	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
//
//
//	// 渲染
//	glClearColor(0, 0, 1, 0);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glBegin(GL_POLYGON);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	glColor3f(1, 1, 1);
//
//	glTexCoord2f(1, 1);
//	glVertex3d(1, 1, 0);
//
//	glTexCoord2f(0, 1);
//	glVertex3d(-1, 1, 0);
//
//	glTexCoord2f(0, 0);
//	glVertex3d(-1, -1, 0);
//
//	glTexCoord2f(1, 0);
//	glVertex3d(1, -1, 0);
//
//	glEnd();
//
//	glFlush();
//	//glutSwapBuffers();
//}
//
//
//// 渲染到纹理
//void RenderToTarget(void)
//{
//	glBindTexture(GL_TEXTURE_2D, 0); // 取消绑定，因为如果不取消，渲染到纹理的时候会使用纹理本身
//
//	// 绑定渲染目标
//	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
//	glViewport(0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT);
//
//	// 渲染
//	glClearColor(1, 1, 0, 1);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glBegin(GL_POLYGON);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	glColor4f(1, 0, 0, 1);
//	glVertex3d(0, 1, 0);
//	glVertex3d(-1, -1, 0);
//	glVertex3d(1, -1, 0);
//
//	glEnd();
//
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}
//
//void Clear(void)
//{
//
//}
//
//void renderScene()
//{
//	RenderToTarget();
//	Render();
//	//Render1();
//}
//






void SetupResource(void)
{
	//glEnable(GL_TEXTURE_2D);
	// 创建纹理
	glGenTextures(1, &rendertarget);
	glBindTexture(GL_TEXTURE_2D, rendertarget);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	/*
	// 创建深度缓冲区
	glGenRenderbuffersEXT(1, &depthbuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthbuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, TEXTURE_WIDTH, TEXTURE_HEIGHT);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
	*/

	// 创建FBO对象
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rendertarget, 0);
	//glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthbuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		printf(" not ok");
	}
}

void Render()
{

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, rendertarget);
	glViewport(0, 0, 512, 512);



	glClearColor(0, 0, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_POLYGON);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1, 1, 1);

	glTexCoord2f(1, 1);
	glVertex3f(0.5f, 0.5f, 0);

	glTexCoord2f(0, 1);
	glVertex3f(-0.5f, 0.5f, 0);

	glTexCoord2f(0, 0);
	glVertex3f(-0.5f, -0.5f, 0);

	glTexCoord2f(1, 0);
	glVertex3f(0.5f, -0.5f, 0);

	glEnd();

	//glutSwapBuffers();
	glFlush();


	//	// 绑定默认FBO（窗体帧缓冲区的ID是0）
	//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//	glBindTexture(GL_TEXTURE_2D, rendertarget);
	//	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	//
	//
	//	// 渲染
	//	glClearColor(0, 0, 1, 0);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//
	//	glBegin(GL_POLYGON);
	//
	//	glMatrixMode(GL_MODELVIEW);
	//	glLoadIdentity();
	//
	//	glColor3f(1, 1, 1);
	//
	//	glTexCoord2f(1, 1);
	//	glVertex3d(1, 1, 0);
	//
	//	glTexCoord2f(0, 1);
	//	glVertex3d(-1, 1, 0);
	//
	//	glTexCoord2f(0, 0);
	//	glVertex3d(-1, -1, 0);
	//
	//	glTexCoord2f(1, 0);
	//	glVertex3d(1, -1, 0);
	//
	//	glEnd();
	//
	//	glFlush();
	//	//glutSwapBuffers();
}







// 渲染到纹理
void RenderToTarget()
{
	glBindTexture(GL_TEXTURE_2D, 0); // 取消绑定，因为如果不取消，渲染到纹理的时候会使用纹理本身

	// 绑定渲染目标
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glViewport(0, 0, 512, 512);

	// 渲染
	glClearColor(1, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_POLYGON);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor4f(1, 0, 0, 1);
	glVertex3d(0, 0.5f, 0);
	glVertex3d(-0.5f, -0.5f, 0);
	glVertex3d(0.5f, -0.5f, 0);

	glEnd();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void display8()
{
	


	//glBindFramebuffer(GL_FRAMEBUFFER, g_framebufferID);
	//glPushAttrib(GL_VIEWPORT_BIT);

	//glViewport(0, 0, 512, 512);

	//glClear(GL_COLOR_BUFFER_BIT);

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, g_texture);


	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);




	//glutSolidTeapot(2.0);


	//glPopAttrib();

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//glClearColor(0.0f,0.0f, 0.0f, 10.f);
	//glClear(GL_COLOR_BUFFER_BIT);

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, g_texture);


	//glutSolidSphere(1.0, 40, 50);

	//glFlush();

	RenderToTarget();
	Render();
}




void initFbo()
{
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &rendertarget);
	glBindTexture(GL_TEXTURE_2D, rendertarget);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rendertarget, 0);


	//glGenRenderbuffers(1, &g_depthbuffer);
	//glBindRenderbuffer(GL_RENDERBUFFER, g_depthbuffer);
	//glRenderbufferStorage(GL_FRAMEBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, g_depthbuffer);

	GLenum state = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (state == GL_FRAMEBUFFER_COMPLETE)
	{
		printf("ok...........");
	}
	else
	{
		printf("false%d",state);
	} 
}

void SetupCamera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45, (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT, NEAR_PLANE, FAR_PLANE);
	gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
	gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);

	// 各种变换应该在GL_MODELVIEW模式下进行
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Z-buffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// 启用2D贴图
	glEnable(GL_TEXTURE_2D);
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
	//initFbo();
	SetupCamera();
	//SetupResource();
	initFbo();
	//Initialize2();
	glutDisplayFunc(display8);
	//glutIdleFunc(myIdle);
	glutMainLoop();
}
