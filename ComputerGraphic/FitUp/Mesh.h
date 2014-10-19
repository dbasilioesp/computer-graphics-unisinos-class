#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <GL\glut.h>


using namespace std;


struct Vertex
{
	float axis[3];
};

struct Face
{
	vector<int> vertexIndices;
};

struct Mesh
{
	vector<Vertex> vertexes;
	vector<Face> faces;
};


Mesh* ReadMeshObject(string filename);
