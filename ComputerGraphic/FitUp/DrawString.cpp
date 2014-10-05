#include "DrawString.h"


void DrawString(int x, int y, const char *string, ...)
{
	char buffer[128];

	va_list arg;
	va_start(arg, string);
	vsprintf(buffer, string, arg);
	va_end(arg);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(0.9f, 0.6f, 0.6f);
	glRasterPos2i(x, y);
	int length = (int)strlen(buffer);
	for (int i = 0; i < length; ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[i]);
		//glutBitmapCharacter(GLUT_BITMAP_9_BY_15, buffer[i]);
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
