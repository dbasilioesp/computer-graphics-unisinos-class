#pragma once
#include <string>
#include <vector>
#include <GL\glut.h>
#include "Mesh.h"

using namespace std;


class Object3D
{
public:
	Object3D(void);
	Object3D(float x, float y, float z, float scale, string meshName);
	~Object3D(void);

	void setColor(int r, int g, int b);
	void Draw(Mesh *mesh);
	void DrawBorderBox(vector<Vertex> *vertexes);

	float x;
	float y;
	float z;
	float scale;
	string meshName;
	int color[3];
};

