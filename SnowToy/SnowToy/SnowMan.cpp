#include "SnowMan.h"

void CreateSnowMan(GLfloat x, GLfloat y, GLfloat z){

	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
		glTranslatef(x, y, z);
		glutSolidSphere(6, 15, 15);
		glTranslatef(0.0, -20.0f, 0.0);
		glutSolidSphere(10, 15, 15);
	glPopMatrix();

}