#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <map>
#include <vector>
#include "Mesh.h"
#include "Camera.h"
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
vector<Object3D*> world;
map<string, Mesh*> meshes;
Object3D *objectSelected;
Camera camera;


void DrawGround();
void DrawHUD();
void SelectNext();
void LoadMeshFiles();
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

	camera.computePosition();
	camera.computeDirection();
	
	LoadMeshFiles();

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


void DrawGround(){

	// Draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
	glColor3f(0.8f, 0.8f, 0.8f);
	for (int i = -100; i < 100; i+=1){
		glBegin(GL_LINES);
			glVertex3f(i, 0.01f, -100);
			glVertex3f(i, 0.01f, 100);
			glVertex3f(-100, 0.01f, i);
			glVertex3f(100, 0.01f, i);
		glEnd();	
	}
}


void DrawHUD(){

	DrawString(10, 20, "[c] Change color");
	DrawString(10, 40, "[+] Grow");
	DrawString(10, 60, "[-] Reduce");
	DrawString(10, 80, "[n] Next");

	DrawString(windowWidth-90, 20, "Scale: %.1f", objectSelected->scale);
	DrawString(10, windowHeight-10, "Colors: %d %d %d", objectSelected->color[0], objectSelected->color[1], objectSelected->color[2]);
	DrawString(windowWidth-120, windowHeight-10, "x:%.0f y:%.0f z:%.0f", camera.x, camera.y, camera.z);
}


void SelectNext(){
	if(objectSelected){
		vector<Object3D*>::iterator it;

		for (it = world.begin() ; it != world.end(); ++it){
			if(objectSelected == *it){
				++it;
				if(it != world.end()){				
					objectSelected = *it;
				} else {
					objectSelected = *world.begin();
				}
				break;
			}
		}
	}
}


void LoadMeshFiles(){

	meshes["venus"] = ReadMeshObject("../objects/venus.obj");
	meshes["cat"] = ReadMeshObject("../objects/cat.obj");
	meshes["cube"] = ReadMeshObject("../objects/cube.obj");
	meshes["cow"] = ReadMeshObject("../objects/cow.obj");
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

}


void DisplayFunc(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

	// Reset transformations
	glLoadIdentity();

	if(camera.deltaMove)
		camera.computePosition();

	if(camera.deltaAngle)
		camera.computeDirection();

	// Set the camera
	gluLookAt(	camera.x, camera.y, camera.z,
				camera.x+camera.lineSightX, camera.y+camera.lineSightY,  camera.z+camera.lineSightZ,
				0.0f, 1.0f,  0.0f);

	DrawHUD();
	
	DrawGround();
	
	for (int i = 0; i < world.size(); i++){
		Mesh *mesh = meshes[world[i]->meshName];
		world[i]->Draw(mesh);
	}

	if(objectSelected){
		vector<Vertex> *vertexes = &meshes[objectSelected->meshName]->vertexes;
		objectSelected->DrawBorderBox(vertexes);
	}

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
		case 'n':
			SelectNext();
			break;
		case '+':
			objectSelected->scale += 0.1;
			break;
		case '-':
			objectSelected->scale -= 0.1;
			break;
		case '1':
			objectSelected = new Object3D(camera.x+camera.lineSightX, 
										  camera.y, 
										  camera.z+camera.lineSightZ, 
										  0.05, "cat");
			world.push_back(objectSelected);
			break;
		case '2':
			objectSelected = new Object3D(camera.x+camera.lineSightX+3.0, 
										  camera.y, 
										  camera.z+camera.lineSightZ+3.0, 
										  1, "cube");
			world.push_back(objectSelected);
			break;
		case '3':
			objectSelected = new Object3D(camera.x+camera.lineSightX+3.0, 
										  camera.y, 
										  camera.z+camera.lineSightZ+3.0, 
										  0.3, "cow");
			world.push_back(objectSelected);
			break;
		case '4':
			objectSelected = new Object3D(camera.x+camera.lineSightX+3.0, 
										  camera.y, 
										  camera.z+camera.lineSightZ+3.0, 
										  0.1, "venus");
			world.push_back(objectSelected);
			break;
	}
}


void PressKey(int key, int xx, int yy) {

	switch (key) {
		case GLUT_KEY_LEFT : camera.deltaAngle = -0.01f; break;
		case GLUT_KEY_RIGHT : camera.deltaAngle = 0.01f; break;
		case GLUT_KEY_UP : camera.deltaMove = 0.5f; break;
		case GLUT_KEY_DOWN : camera.deltaMove = -0.5f; break;
	}

}


void ReleaseKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT : camera.deltaAngle = 0.0f;break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : camera.deltaMove = 0;break;
	}
}
