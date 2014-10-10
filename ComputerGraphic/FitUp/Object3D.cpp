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
