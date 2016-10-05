#include<Windows.h>
#include<gl\GL.h>
#include<gl\GLU.h>
#include <cmath>
#include "OpenGLApp.h"


OpenGLApp::OpenGLApp()
{
}


OpenGLApp::~OpenGLApp()
{
}


bool OpenGLApp::Initialize()	//initialize your opengl scene
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	return true;
}	
bool OpenGLApp::Shutdown()	//shut down your scene
{
	return true;
}

//used to setup your opengl camera and drawing area
void OpenGLApp::SetupProjection(int width, int height){
	if (height == 0)
	{
		height = 1;
	}

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// you need 3 things to create a frustum
	// 1. Field of view (52.0f here)
	// 2. aspect ratio of screen (width/height of window)
	// 3. near and far plane (1, and 1000)
	gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	m_windowWidth = width;
	m_windowHeight = height;
}

void OpenGLApp::Prepare(float dt)
{

}
void OpenGLApp::Render()
{
	static float angle = 0.0f;


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -5.0f);

	glColor3f(0.73f, 0.16f, 0.96f); //purple

	//gluLookAt - move the camera and change the 
	// direction it is looking

	//syntax for gluLookAt:
	//gluLookAt  (x, y, z //location of camera
	//			  x, y, z //where it's looking
	//			  x, y, z) //which way is up
	
	gluLookAt(0.0f, 5.0f, 0.1,
			  0.0f, 0.0f, 0.0f,
		      0.0f, 1.0f, 0.0f);

	//set polymode - on the front draw lines only
	glPolygonMode(GL_FRONT, GL_LINE);
	glPushMatrix(); //save current model view settings (no rot, no scale, no translate)
		glTranslatef(-4.0f, 0.0f, 0.0f);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glColor3f(1.0f, 0.0f, 0.0f); //red
		Draw2DSquare();
	glPopMatrix(); //restore the saved modelview settings (no rot, no scale, no translate)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //restore default polymode
	

	//green square, back points, translate -2 x
	glPolygonMode(GL_FRONT, GL_POINT);
	glPushMatrix(); //save current model view settings (no rot, no scale, no translate)
	glTranslatef(-2.0f, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f); //green
	Draw2DSquare();
	glPopMatrix(); //restore the saved modelview settings (no rot, no scale, no translate)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //restore default polymode

	//blue, fill front and back, no translation
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix(); //save current model view settings (no rot, no scale, no translate)
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f); //blue
	Draw2DSquare();
	glPopMatrix(); //restore the saved modelview settings (no rot, no scale, no translate)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //restore default polymode

	//purple, lines on the back, translate 2 x
	glPolygonMode(GL_BACK, GL_LINE);
	glPushMatrix(); //save current model view settings (no rot, no scale, no translate)
	glTranslatef(2.0f, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 0.0f, 1.0f); //purple
	Draw2DSquare();
	glPopMatrix(); //restore the saved modelview settings (no rot, no scale, no translate)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //restore default polymode

	//yellow, line on front and back, translate 4 x
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix(); //save current model view settings (no rot, no scale, no translate)
	glTranslatef(4.0f, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 0.0f); //yellow
	Draw2DSquare();
	glPopMatrix(); //restore the saved modelview settings (no rot, no scale, no translate)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //restore default polymode


	//make this funciton call if you want to see the grid
	//DrawGrid();

	//increase the angle
	angle += 1.0f;

}

void OpenGLApp::DrawGrid()
{
	//increase the size of drawn points
	glPointSize(3.0f);

	glBegin(GL_LINES);
	//change the color to blue
	glColor3f(0.0f, 0.0, 1.0f);

	//vertical
	for (float x = 8; x >= -8; x--)
	{
		glVertex3f(x, 5.0f, 0.0f);
		glVertex3f(x, -5.0f, 0.0f);
	}
	//horizontal
	for (float y = 5; y >= -5; y--)
	{
		glVertex3f(8.0f, y, 0.0f);
		glVertex3f(-8.0f, y, 0.0f);
	}

	glEnd();
	
	//we are going to draw below
	glBegin(GL_POINTS);

		//change color to white
		glColor3f(1.0f, 1.0f, 1.0f);

		//draw the points on the y-axis
		for (float y = 5; y >= -5; y--)
		{
			glVertex3f(0.0f, y, 0.0f);
		}

		//draw the points on the x-axis
		for (float x = 8; x >= -8; x--)
		{
			glVertex3f(x, 0.0, 0.0f);
		}

		//set the color to red
		glColor3f(1.0f, 0.0f, 0.0f);
		//draw the orgin
		glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();

}

void OpenGLApp::Draw2DSquare()
{
	
	glBegin(GL_POLYGON);
		glVertex3f(-0.5f, 0.0f, 0.0f); // (x,y,z)
			//glColor3f(0.0f, 1.0f, 0.0f); //blue
		glVertex3f(0.5f, 0.0f, 0.0f);
			//glColor3f(1.0f, 0.0f, 0.0f); //red
		glVertex3f(0.5f, 0.0f, -1.0f);
			//glColor3f(0.0f, 0.0f, 1.0f); //green
		glVertex3f(-0.5f, 0.0f, -1.0f);
		
	glEnd();
}