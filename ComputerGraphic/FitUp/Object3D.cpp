#include "Object3D.h"


Object3D::Object3D(void)
{
	x = 0;
	y = 0;
	z = 0;
	meshName = "";
	scale = 1;
	color[0] = 100;
	color[1] = 255;
	color[2] = 255;
}


Object3D::Object3D(float x, float y, float z, float scale, string meshName)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->meshName = meshName;
	this->scale = scale;
	color[0] = 100;
	color[1] = 255;
	color[2] = 255;
}


Object3D::~Object3D(void)
{
}


void Object3D::setColor(int r, int g, int b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}


void Object3D::Draw(Mesh *mesh)
{
	glPushMatrix();
		
		glTranslatef(x, y, z);
		
		if(scale != 1.0){
			glScalef(scale, scale, scale);
		}
		
		for (int i = 0; i < mesh->faces.size(); i++){

			int size = mesh->faces[i].vertexIndices.size();
			
			if(size == 3){
				glBegin(GL_TRIANGLES);
			}else{
				glBegin(GL_POLYGON);
			}

			for (int j = 0; j < size; j++){
				int index = mesh->faces[i].vertexIndices[j];
				Vertex vertex = mesh->vertexes[index];
				glColor3ub(color[0], color[1], color[2]);
				glVertex3f(vertex.axis[0], vertex.axis[1], vertex.axis[2]);
			}

			glEnd();
		}

	glPopMatrix();
}


void Object3D::DrawBorderBox(vector<Vertex> *vertexes){

	float majorX = 0;
		float minorX = 0;
		float majorY = 0;
		float minorY = 0;
		float majorZ = 0;
		float minorZ = 0;
	
		for (int i = 0; i < vertexes->size(); i++)
		{
			float *axis = vertexes->at(i).axis;
		
			if(axis[0] > majorX){
				majorX = axis[0];
			}
			if(axis[1] > majorY){
				majorY = axis[1];
			}
			if(axis[2] > majorZ){
				majorZ = axis[2];
			}
			if(axis[0] < minorX){
				minorX = axis[0];
			}
			if(axis[1] < minorY){
				minorY = axis[1];
			}
			if(axis[2] < minorZ){
				minorZ = axis[2];
			}
		}

		glPushMatrix();
			glTranslatef(x, y, z);
			if(scale != 1.0){
				glScalef(scale, scale, scale);
			}
			glLineWidth(2);
			glColor3ub(255, 0, 0);
			glBegin(GL_LINES);
				glVertex3f( majorX+0.2, majorY+0.2, majorZ+0.2);
				glVertex3f( majorX+0.2, majorY+0.2, minorZ-0.2);
				glVertex3f( majorX+0.2, minorY-0.2, minorZ-0.2);
				glVertex3f( majorX+0.2, minorY-0.2, majorZ+0.2);
				glVertex3f( minorX-0.2, minorY-0.2, majorZ+0.2);
				glVertex3f( minorX-0.2, minorY-0.2, minorZ-0.2);
				glVertex3f( minorX-0.2, majorY+0.2, minorZ-0.2);
				glVertex3f( minorX-0.2, majorY+0.2, majorZ+0.2);
				glVertex3f( majorX+0.2, majorY+0.2, minorZ-0.2);
				glVertex3f( minorX-0.2, majorY+0.2, minorZ-0.2);
				glVertex3f( majorX+0.2, majorY+0.2, majorZ+0.2);
				glVertex3f( minorX-0.2, majorY+0.2, majorZ+0.2);
				glVertex3f( majorX+0.2, majorY+0.2, majorZ+0.2);
				glVertex3f( majorX+0.2, minorY-0.2, majorZ+0.2);
				glVertex3f( minorX-0.2, majorY+0.2, majorZ+0.2);
				glVertex3f( minorX-0.2, minorY-0.2, majorZ+0.2);
				glVertex3f( minorX-0.2, majorY+0.2, minorZ-0.2);
				glVertex3f( minorX-0.2, minorY-0.2, minorZ-0.2);
				glVertex3f( majorX+0.2, majorY+0.2, minorZ-0.2);
				glVertex3f( majorX+0.2, minorY-0.2, minorZ-0.2);
				glVertex3f( majorX+0.2, minorY-0.2, minorZ-0.2);
				glVertex3f( minorX-0.2, minorY-0.2, minorZ-0.2);
				glVertex3f( majorX+0.2, minorY-0.2, majorZ+0.2);
				glVertex3f( minorX-0.2, minorY-0.2, majorZ+0.2);
			glEnd();
		glPopMatrix();

}