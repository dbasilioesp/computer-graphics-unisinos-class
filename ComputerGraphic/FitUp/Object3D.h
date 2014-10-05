#pragma once
#include <string>

using namespace std;


class Object3D
{
public:
	Object3D(void);
	Object3D(float x, float y, float z, string meshName);
	~Object3D(void);

	float x;
	float y;
	float z;
	string meshName;
};

