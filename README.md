Computer Graphic Unisinos Class
===============================

Here I will put the projects that I will be developing along the semester.


## TeaPot

### Perspective Projection

Here you will set the perspective projection and the position of the observator (camera) and the target.

```c++
void SetVisualization(void)
{
    // Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);

	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
    gluPerspective(fovy, fAspect, 0.0, 500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);

	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
    gluLookAt(0, 80, 250, 0, 0, 0, 0, 1, 0);
}


void ResizeFunc(GLsizei width, GLsizei height)
{
	// Para previnir uma divisão por zero
	if ( height == 0 ) height = 1;

	// Especifica o tamanho da viewport
    glViewport(0, 0, width, height);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)width / (GLfloat)height;

	SetVisualization();
}


```

### Drawing TeaPot

Calling function like __glutWireTeapot__ you can draw samples of Glut.

```c++
void DisplayFunc(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 1.0f);

	// Desenha o teapot com a cor corrente (wire-frame)
	glutWireTeapot(50.0f);

	// Executa os comandos OpenGL
	glutSwapBuffers();
 }
```
