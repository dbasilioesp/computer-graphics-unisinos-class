// TeaPot3D.c - Isabel H. Manssour
// Um programa OpenGL que exemplifica a visualiza��o 
// de objetos 3D.
// Este c�digo est� baseado nos exemplos dispon�veis no livro 
// "OpenGL SuperBible", 2nd Edition, de Richard S. e Wright Jr.

#include <gl/glut.h>

GLfloat fovy = 45;
GLfloat	fAspect;
GLfloat angleTea = 30.0f;


void DisplayFunc(void);
void SetProjectionMode(void);
void ReshapeFunc(GLsizei w, GLsizei h);
void MouseFunc(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);


int main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(350,300);
	glutCreateWindow("Visualizacao 3D");
	
	glutDisplayFunc(DisplayFunc);
    glutReshapeFunc(ReshapeFunc);
	glutMouseFunc(MouseFunc);
	glutKeyboardFunc(Keyboard);

	glutMainLoop();
}


void DisplayFunc(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);

	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posi��o do observador e do alvo
    gluLookAt(0, 80, 250, 
			  0, 0, 0, 
			  0, 1, 0);

	glColor3f(0.0f, 0.0f, 1.0f);
	glutWireTeapot(50.0f);
	
	glutSwapBuffers();
 }

// Fun��o usada para especificar o volume de visualiza��o
void SetProjectionMode(void)
{
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);

	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();

	// Especifica a proje��o perspectiva
    gluPerspective(fovy, fAspect, 0.0, 500);

}


void ReshapeFunc(GLsizei w, GLsizei h)
{
	// Para previnir uma divis�o por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
    glViewport(0, 0, w, h);
 
	// Calcula a corre��o de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	SetProjectionMode();
}


void MouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN)  // Zoom-in
			if (fovy >= 10)
				fovy -= 5;
	
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) // Zoom-out
			if (fovy <= 130)
				fovy += 5;
	
	SetProjectionMode();
	glutPostRedisplay();
}


void Keyboard(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 27:
		exit(0);
		break;
	}

	glutPostRedisplay();
}

