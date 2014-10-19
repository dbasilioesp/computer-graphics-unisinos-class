#pragma once
#include <math.h>


class Camera {

public:
	Camera(void);
	~Camera(void);

	void computePosition();
	void computeDirection();

	// angle of rotation for the camera direction
	float angle;

	// actual vector representing the camera's direction
	float lineSightX;
	float lineSightY;
	float lineSightZ;
	// camera position
	float x;
	float y;
	float z;
	float deltaAngle;
	float deltaMove;
};