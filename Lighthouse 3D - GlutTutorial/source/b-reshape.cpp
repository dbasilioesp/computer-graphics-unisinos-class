
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


void changeSize(int width, int height) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (height == 0)
		height = 1;
	float ratio =  width * 1.0 / height;

    // Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

    // Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, width, height);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
		glVertex3f(-2.0, -2.0, -5.0);
		glVertex3f( 2.0,  0.0, -5.0);
		glVertex3f( 0.0,  2.0, -5.0);
	glEnd();

	glutSwapBuffers();
}


int main(int argc, char **argv) {

    // init GLUT and create window
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");

	// register callbacks
    glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

    // enter GLUT event processing loop
	glutMainLoop();
	
	return 1;
}