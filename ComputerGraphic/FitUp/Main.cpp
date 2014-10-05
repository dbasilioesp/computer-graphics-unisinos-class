#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <map>
#include <vector>
#include "MeshReading.h"
#include "DrawString.h"
#include "Object3D.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;


// angle of rotation for the camera direction
float angle = 2.0f;
// actual vector representing the camera's direction
float lineSightX = 0.0f;
float lineSightZ = -1.0f;
// camera position
float x = 0.0f;
float z = 5.0f;
float deltaAngle = 0.0f;
float deltaMove = 0.0f;
map<string, Mesh*> meshes;
vector<Object3D> world;


void LoadingMeshes(){

	meshes["venus"] = ReadMeshObject("../objects/venus.obj");
	meshes["cat"] = ReadMeshObject("../objects/cat.obj");

}


void computePosition(float deltaMove) {

	x += deltaMove * lineSightX * 0.1f;
	z += deltaMove * lineSightZ * 0.1f;
}

void computeDirection(float deltaAngle) {

	angle += deltaAngle;
	lineSightX = sin(angle);
	lineSightZ = -cos(angle);
}


void ReshapeFunc(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}


void DisplayFunc(void) {

	if (deltaMove)
		computePosition(deltaMove);

	if (deltaAngle)
		computeDirection(deltaAngle);

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	gluLookAt(	x, 1.0f, z,
				x+lineSightX, 1.0f,  z+lineSightZ,
				0.0f, 1.0f,  0.0f);

	// Draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
	
	Object3D *object;
	for (int i = 0; i < world.size(); i++)
	{
		object = &world[i];
		glPushMatrix();
			glTranslatef(object->x, object->y, object->z);
			DrawMesh(meshes[object->meshName]);
		glPopMatrix();
	}
	
	DrawString(10, 20, "Testing");

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy) {

	if (key == 27)
		exit(0);

	switch(key){
		case '1':
			break;
	}
}

void pressKey(int key, int xx, int yy) {

	switch (key) {
		case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
		case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
		case GLUT_KEY_UP : deltaMove = 0.5f; break;
		case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
	}

}

void releaseKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : deltaMove = 0;break;
	}
}

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Objects 3D");

	// register callbacks
	glutDisplayFunc(DisplayFunc);
	glutIdleFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutIgnoreKeyRepeat(1);  // here are the new entries
	glutSpecialUpFunc(releaseKey);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	computePosition(deltaMove);
	computeDirection(deltaAngle);
	
	LoadingMeshes();

	Object3D venus(10.0, 2.0, 10.0, "venus");
	world.push_back(venus);

	Object3D cat(10.0, 0.0, 30.0, "cat");
	world.push_back(cat);

	// enter GLUT event processing cycle
	glutMainLoop();
	
	return 1;
}