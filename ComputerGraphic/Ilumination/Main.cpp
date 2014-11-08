#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define PI 3.1415


GLint WIDTH = 600;
GLint HEIGHT= 400;

GLfloat eyes[3] = {0.0, 7.0, 0.0};
GLfloat centers[3] = {0.0, 3.0, 0.0};
GLfloat tetaxz = 0;
GLfloat raioxz = 6;
GLint gouraud = 1;

GLfloat plano_difusa[]    = { 0.5, 0.5, 0.0, 1.0 };
GLfloat plano_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat plano_brilho[]    = { 50.0 };

GLfloat mat_a_difusa[]    = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_a_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_a_brilho[]    = { 50.0 };

GLfloat mat_b_difusa[]    = { 0.7, 0.7, 0.7, 0.5 };
GLfloat mat_b_especular[] = { 1.0, 1.0, 1.0, 0.5 };
GLfloat mat_b_brilho[]    = { 50.0 };

GLfloat posicao_luz0[]    = { 0.0, 10.0, 0.0, 1.0};
GLfloat cor_luz0[]        = { 1.0, 1.0, 1.0, 1.0};
GLfloat cor_luz0_amb[]    = { 0.3, 0.3, 0.3, 1.0};

GLfloat posicao_luz1[]    = { 0.0, 10.0, 5.0, 1.0};
GLfloat cor_luz1[]        = { 0.0, 0.0, 1.0, 1.0};
GLfloat direcao_luz1[]    = { 0.0, -10.0, -5.0, 1.0};
GLint   spot_luz1         = 30;

GLfloat colorless[]         = { 0.0, 0.0, 0.0, 1.0};



void reshape(int width, int height){
    WIDTH = width;
    HEIGHT = height;
    glViewport(0,0,(GLint)width,(GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0,width/(float)height,0.1,30.0);
    glMatrixMode(GL_MODELVIEW);
}

void display(void){

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    glDepthMask(GL_TRUE);
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    if(gouraud){
        glShadeModel(GL_SMOOTH);
    }
    else{
        glShadeModel(GL_FLAT);
    }
    
    glPushMatrix();
    
    /* calcula a posicao do observador */
    eyes[0] = raioxz * cos(2*PI*tetaxz/360);
    eyes[2] = raioxz * sin(2*PI*tetaxz/360);

    gluLookAt(eyes[0], eyes[1], eyes[2], centers[0], centers[1], centers[2], 0.0, 1.0, 0.0);
    
    /* propriedades do material do plano */
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, plano_difusa);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, plano_especular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, plano_brilho);
    
    /* desenha o plano */
    glNormal3f(0,1,0);
    glBegin(GL_QUADS);
    glVertex3f(-10,0,10);
    glVertex3f(10,0,10);
    glVertex3f(10,0,-10);
    glVertex3f(-10,0,-10);
    glEnd();
    
    glPushMatrix();
    glTranslatef(posicao_luz0[0],posicao_luz0[1],posicao_luz0[2]);
    glColor3f(1,0,0);
    glMaterialfv(GL_FRONT, GL_EMISSION, cor_luz0);
    glutSolidSphere(0.3,5,5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(posicao_luz1[0],posicao_luz1[1],posicao_luz1[2]);
    glMaterialfv(GL_FRONT, GL_EMISSION, cor_luz1);
    glutSolidSphere(0.3,5,5);
    glPopMatrix();
    
    glMaterialfv(GL_FRONT, GL_EMISSION, colorless);
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_a_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_a_especular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_a_brilho);
    
	GLint radius = 1.5;
	GLint slices = 30;
	GLint stacks = 30;

    glPushMatrix();
    glTranslatef(0.0,3.0,-3.0);
    glutSolidSphere(radius, slices, stacks);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_b_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_b_especular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_b_brilho);

    glTranslatef(0.0, 3.0, 3.0);
    glutSolidSphere(radius, 30, stacks);
    
	glPopMatrix();
    glutSwapBuffers();
}

void special(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_UP:
            eyes[1]=eyes[1]+1;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            eyes[1] =eyes[1]-1;
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            tetaxz=tetaxz+2;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            tetaxz=tetaxz-2;
            glutPostRedisplay();
            break;
    }
}

void keyboard(unsigned char key, int x, int y){
    switch (key) {
        case 27:
            exit(0);
            break;
        case 'g':
            gouraud = !gouraud;
            glutPostRedisplay();
            break;
        case 'r':
            raioxz=raioxz+1;
            glutPostRedisplay();
            break;
        case 'R':
            if(raioxz>1){
                raioxz=raioxz-1;
                glutPostRedisplay();
            }
            break;
    }
}


void init(){
    gouraud=1;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz0_amb);
    glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz0);
    
    glLightfv(GL_LIGHT1, GL_DIFFUSE, cor_luz1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, cor_luz1);
    glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, spot_luz1);
    glLightfv(GL_LIGHT1, GL_POSITION, posicao_luz1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direcao_luz1);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
}

void menu(int value){
    switch (value) {
        case 0:
            mat_a_especular[0]=mat_a_especular[1]=mat_a_especular[2]=0.0;
            break;
        case 1:
            mat_a_especular[0]=mat_a_especular[1]=mat_a_especular[2]=0.5;
            break;
        case 2:
            mat_a_especular[0]=mat_a_especular[1]=mat_a_especular[2]=1.0;
            break;
        case 3:
            mat_a_difusa[0]=mat_a_difusa[1]=mat_a_difusa[2]=0.0;
            break;
        case 4:
            mat_a_difusa[0]=mat_a_difusa[1]=mat_a_difusa[2]=0.5;
            break;
        case 5:
            mat_a_difusa[0]=mat_a_difusa[1]=mat_a_difusa[2]=1.0;
            break;
    }
    glutPostRedisplay();
}


int main(int argc,char **argv){
	
	glutInit(&argc, argv);
    glutInitWindowPosition(400, 250);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
    
    if(!glutCreateWindow("Modelos de iluminacao")) {
        fprintf(stderr,"Error opening a window.\n");
        exit(-1);
    }
    
    init();
    
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    glutCreateMenu(menu);
    glutAddMenuEntry("-sem spec", 0);
    glutAddMenuEntry("-spec média", 1);
    glutAddMenuEntry("-spec alta", 2);
    glutAddMenuEntry("-sem difusa", 3);
    glutAddMenuEntry("-difusa média", 4);
    glutAddMenuEntry("-difusa alta", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    glutMainLoop();
    return(0);
}
