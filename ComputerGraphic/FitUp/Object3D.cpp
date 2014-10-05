#include "Object3D.h"


Object3D::Object3D(void)
{
	x = 0;
	y = 0;
	z = 0;
	meshName = "";
}


Object3D::Object3D(float x, float y, float z, string meshName)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->meshName = meshName;
}


Object3D::~Object3D(void)
{
}
