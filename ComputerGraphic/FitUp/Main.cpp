#include <stdlib.h>
#include <math.h>
#include "MeshReading.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


// angle of rotation for the camera direction
float angle = 2.0f;
// actual vector representing the camera's direction
float lineSightX = 0.0f;
float lineSightZ = -1.0f;
// XZ position of the camera
float x = 0.0f;
float z = 5.0f;
// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0.0f;
Mesh *mesh;


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
	
	glPushMatrix();
		glTranslatef(10.0, 0.0, 10.0);
		DrawMesh(mesh);
	glPopMatrix();
	
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy) {

	if (key == 27)
		exit(0);

	switch(key){
		case '1':
			mesh = ReadMeshObject("../objects/venus.obj");
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

	mesh = ReadMeshObject("../objects/cat.obj");

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

	// enter GLUT event processing cycle
	glutMainLoop();
	
	return 1;
}