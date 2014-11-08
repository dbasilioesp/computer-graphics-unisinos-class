#include <windows.h>
#include <stdio.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glut.h>
#include "tgaload.h"


#define MAX_NO_TEXTURES 2  // Qtd máxima de texturas a serem usadas no programa
#define OBJETO_ESQUERDA 0
#define OBJETO_DIREITA  1

// vetor com os números das texturas
GLuint texture_id[MAX_NO_TEXTURES];
float rotateX;
float rotateY;
float rotateZ;
float ratio;


void initTexture (void)
{

	image_t temp_image; // variável que irá armazenar a textura a ser usada

	// Habilita o uso de textura 
	glEnable ( GL_TEXTURE_2D );

	// Define a forma de armazenamento dos pixels na textura (1= alihamento por byte)
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );

	// Define quantas texturas serão usadas no programa 
	glGenTextures (1, texture_id);  // 1 = uma textura;
									// texture_id = vetor que guardas os números das texturas

	// Define os números da textura dos cubos
	texture_id[OBJETO_ESQUERDA] = 1001;
	texture_id[OBJETO_DIREITA] = 1002;

	// ****
	// Define a textura do objeto da ESQUERDA
	// ****

	// Define que tipo de textura será usada
	// GL_TEXTURE_2D ==> define que será usada uma textura 2D (bitmaps)
	// texture_id[OBJETO_ESQUERDA]  ==> define o número da textura 
	glBindTexture ( GL_TEXTURE_2D, texture_id[OBJETO_ESQUERDA] );
	
	// Carrega a primeira imagem .TGA 
	tgaLoad  ( "YODA.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY );


	glBindTexture ( GL_TEXTURE_2D, texture_id[OBJETO_DIREITA] );
	tgaLoad  ( "PEOPLE.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY );

}


void init(void)
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_CULL_FACE );
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
}


void reshape( int w, int h )
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the clipping volume
	gluPerspective(80, ratio, 1, 200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 30,
		      0,0,10,
			  0.0f,1.0f,0.0f);
}


void DesenhaCubo (GLuint textureId)
{
	// define qual das texturas usar
	glBindTexture(GL_TEXTURE_2D, textureId);
	
	glBegin ( GL_QUADS );
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
	

}


void display( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	
	glPushMatrix();
		glTranslatef ( -3.0, 0.0, -5.0 );
		glRotatef ( rotateX, 1.0, 0.0, 0.0 );
		glRotatef ( rotateY, 0.0, 1.0, 0.0 );
		glRotatef ( rotateZ, 0.0, 0.0, 1.0 );

		DesenhaCubo (texture_id[OBJETO_ESQUERDA]);	

	glPopMatrix();

	glPushMatrix();
		glTranslatef ( +3.0, 0.0, -5.0 );
		glRotatef ( rotateX, 1.0, 0.0, 0.0 );
		glRotatef ( rotateY, 0.0, 1.0, 0.0 );
		glRotatef ( rotateZ, 0.0, 0.0, 1.0 );

		DesenhaCubo (texture_id[OBJETO_DIREITA]);	

	glPopMatrix();
	
	rotateX += 0.3f;
	rotateY += 0.2f;
	rotateZ += 0.4f;
	glutSwapBuffers();
}


void keyboard ( unsigned char key, int x, int y )  
{
	switch ( key ) 
	{
    case 27:        // When Escape Is Pressed...
      exit ( 0 );   // Exit The Program
      break;        // Ready For Next Case
    default:        // Now Wrap It Up
      break;
  }
}


void arrow_keys ( int a_keys, int x, int y )  
{
	switch ( a_keys ) 
	{
		case GLUT_KEY_UP:     // When Up Arrow Is Pressed...
			glutFullScreen ( ); // Go Into Full Screen Mode
			break;
	    case GLUT_KEY_DOWN:               // When Down Arrow Is Pressed...
			glutInitWindowSize  ( 700, 500 ); 
			break;
		default:
			break;
	}
}


void main ( int argc, char** argv )   
{
	glutInit (&argc, argv); 
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition (0,0);
	glutInitWindowSize ( 700, 500 ); 
	glutCreateWindow ("Tópicos em Computação Gráfica - Teste com Texturas.");
		
	init ();
	initTexture ();
		
	glutDisplayFunc (display);  
	glutReshapeFunc (reshape);
	glutKeyboardFunc (keyboard);
	glutSpecialFunc (arrow_keys);
	glutIdleFunc (display);
	glutMainLoop ();          
}




