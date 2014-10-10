#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <map>
#include <vector>
#include "Mesh.h"
#include "DrawString.h"
#include "Object3D.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

float windowWidth = 800;
float windowHeight = 600;
// angle of rotation for the camera direction
float angle = 2.0f;
// actual vector representing the camera's direction
float lineSightX = 0.0f;
float lineSightY = 0.0f;
float lineSightZ = -1.0f;
// camera position
float x = 0.0f;
float y = 1.0f;
float z = 5.0f;
float deltaAngle = 0.0f;
float deltaMove = 0.0f;
map<string, Mesh*> meshes;
vector<Object3D*> world;
Object3D *objectSelected;

void DrawObject(Object3D *object);
void DrawHUD();
void LoadMeshes();
void ComputePosition(float deltaMove);
void ComputeDirection(float deltaAngle);
void ReshapeFunc(int w, int h);
void DisplayFunc(void);
void ProcessNormalKeys(unsigned char key, int xx, int yy);
void PressKey(int key, int xx, int yy);
void ReleaseKey(int key, int x, int y);


int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Objects 3D");

	// register callbacks
	glutDisplayFunc(DisplayFunc);
	glutIdleFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutKeyboardFunc(ProcessNormalKeys);
	glutSpecialFunc(PressKey);
	glutIgnoreKeyRepeat(1);  // here are the new entries
	glutSpecialUpFunc(ReleaseKey);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	ComputePosition(deltaMove);
	ComputeDirection(deltaAngle);
	
	LoadMeshes();

	Object3D *venus = new Object3D(10.0, 2.0, 10.0, 0.5, "venus");
	venus->setColor(44, 44, 80);
	objectSelected = venus;
	world.push_back(venus);

	Object3D *cat = new Object3D(10.0, 0.0, 30.0, 0.3, "cat");
	cat->setColor(144, 104, 20);
	world.push_back(cat);

	glutMainLoop();
	
	return 1;
}


void DrawObject(Object3D *object){

	glPushMatrix();
		glTranslatef(object->x, object->y, object->z);
		if(object->scale != 1.0){
			glScalef(object->scale, object->scale, object->scale);
		}
			
		Mesh *mesh = meshes[object->meshName];

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < mesh->polygons.size(); i++){
		
			int index0 = mesh->polygons[i].vertexes[0];
			int index1 = mesh->polygons[i].vertexes[1];
			int index2 = mesh->polygons[i].vertexes[2];

			Vertex vertex0 = mesh->vertexes[index0];
			Vertex vertex1 = mesh->vertexes[index1];
			Vertex vertex2 = mesh->vertexes[index2];

			glColor3ub(object->color[0], object->color[1], object->color[2]);
			
			glVertex3f(vertex0.axis[0], vertex0.axis[1], vertex0.axis[2]);
			glVertex3f(vertex1.axis[0], vertex1.axis[1], vertex1.axis[2]);
			glVertex3f(vertex2.axis[0], vertex2.axis[1], vertex2.axis[2]);
		}
		glEnd();


	glPopMatrix();

}


void LoadMeshes(){

	meshes["venus"] = ReadMeshObject("../objects/venus.obj");
	meshes["cat"] = ReadMeshObject("../objects/cat.obj");
	meshes["cube"] = ReadMeshObject("../objects/cube.obj");
	meshes["cow"] = ReadMeshObject("../objects/cow.obj");
}


void ComputePosition(float deltaMove){

	x += deltaMove * lineSightX * 0.1f;
	z += deltaMove * lineSightZ * 0.1f;
}


void ComputeDirection(float deltaAngle){

	angle += deltaAngle;
	lineSightX = sin(angle);
	lineSightZ = -cos(angle);
}


void DrawHUD(){

	DrawString(10, 20, "[c] Change color");
	DrawString(10, 40, "[+] Grow");
	DrawString(10, 60, "[-] Reduce");

	DrawString(windowWidth-90, 20, "Scale: %.1f", objectSelected->scale);
	DrawString(10, windowHeight-10, "Colors: %d %d %d", objectSelected->color[0], objectSelected->color[1], objectSelected->color[2]);
	DrawString(windowWidth-120, windowHeight-10, "x:%.0f y:%.0f z:%.0f", x, y, z);
}


void ReshapeFunc(int w, int h){

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
		ComputePosition(deltaMove);

	if (deltaAngle)
		ComputeDirection(deltaAngle);

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	gluLookAt(	x, y, z,
				x+lineSightX, y+lineSightY,  z+lineSightZ,
				0.0f, 1.0f,  0.0f);

	// Draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
	
	for (int i = 0; i < world.size(); i++)
	{
		DrawObject(world[i]);
	}

	DrawHUD();

	glutSwapBuffers();
}


void ProcessNormalKeys(unsigned char key, int xx, int yy) {

	if (key == 27)
		exit(0);

	int r, g, b;

	switch(key){
		case 'c':
			r = rand() % 256;
			g = rand() % 256;
			b = rand() % 256;
			objectSelected->setColor(r, g, b);
			break;
		case '+':
			objectSelected->scale += 0.1;
			break;
		case '-':
			objectSelected->scale -= 0.1;
			break;
		case '1':
			objectSelected = new Object3D(x+lineSightX, y, z+lineSightZ, 0.05, "cat");
			world.push_back(objectSelected);
			break;
		case '2':
			objectSelected = new Object3D(x+lineSightX+3.0, y, z+lineSightZ+3.0, 1, "cube");
			world.push_back(objectSelected);
			break;
		case '3':
			objectSelected = new Object3D(x+lineSightX+3.0, y, z+lineSightZ+3.0, 0.3, "cow");
			world.push_back(objectSelected);
			break;
		case '4':
			objectSelected = new Object3D(x+lineSightX+3.0, y, z+lineSightZ+3.0, 0.1, "venus");
			world.push_back(objectSelected);
			break;
	}
}


void PressKey(int key, int xx, int yy) {

	switch (key) {
		case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
		case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
		case GLUT_KEY_UP : deltaMove = 0.5f; break;
		case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
	}

}


void ReleaseKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : deltaMove = 0;break;
	}
}
