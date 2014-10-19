#include "Camera.h"


Camera::Camera(void)
{
	angle = 2.0f;
	lineSightX = 0.0f;
	lineSightY = 0.0f;
	lineSightZ = -1.0f;
	x = 0.0f;
	y = 1.0f;
	z = 5.0f;
	deltaAngle = 0.0f;
	deltaMove = 0.0f;
}


Camera::~Camera(void)
{
}


void Camera::computePosition(){
	
	x += deltaMove * lineSightX * 0.1f;
	z += deltaMove * lineSightZ * 0.1f;
}


void Camera::computeDirection(){
	
		angle += deltaAngle;
		lineSightX = sin(angle);
		lineSightZ = -cos(angle);
}