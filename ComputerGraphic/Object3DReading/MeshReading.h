#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <GL\glut.h>


using namespace std;


struct Vertex
{
	float axis[3];
};

struct Polygon
{
	vector<int> vertexes;
};

struct Mesh
{
	vector<Vertex> vertexes;
	vector<Polygon> polygons;
};


Mesh* ReadMeshObject(string filename)
{

	Mesh *mesh = new Mesh;
	ifstream infile;
	string line, token;
	int vertexReference = 0;
	
	infile.open(filename);

	while(!infile.eof()){
		
		infile >> token;

		if(token == "#"){
			getline(infile, line);
			continue;
		}

		if(token == "v"){

			float x, y, z;
			Vertex vertex;
				
			infile >> x;
			infile >> y;
			infile >> z;

			vertex.axis[0] = x;
			vertex.axis[1] = y;
			vertex.axis[2] = z;

			mesh->vertexes.push_back(vertex);
		}
			
		if(token == "vn"){
			getline(infile, line);
			continue;
		}

		if(token == "f"){
			
			Polygon polygon;
			
			for (int i = 0; i < 3; i++){
				infile >> vertexReference;
				polygon.vertexes.push_back(vertexReference - 1);
			}
			
			mesh->polygons.push_back(polygon);
		}

	}
	
	infile.close();

	return mesh;
}


void DrawMesh(Mesh *mesh)
{
	
	glTranslatef(0.0, 2.0, 0.0);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < mesh->polygons.size(); i++){
		
		int index0 = mesh->polygons[i].vertexes[0];
		int index1 = mesh->polygons[i].vertexes[1];
		int index2 = mesh->polygons[i].vertexes[2];

		Vertex vertex0 = mesh->vertexes[index0];
		Vertex vertex1 = mesh->vertexes[index1];
		Vertex vertex2 = mesh->vertexes[index2];

		glColor3f(0.4f, 0.9f , 0.4f);
		glVertex3f(vertex0.axis[0], vertex0.axis[1], vertex0.axis[2]);
		glColor3f(0.9f, 0.4f , 0.4f);
		glVertex3f(vertex1.axis[0], vertex1.axis[1], vertex1.axis[2]);
		glColor3f(0.4f, 0.4f , 0.9f);
		glVertex3f(vertex2.axis[0], vertex2.axis[1], vertex2.axis[2]);	
	}
	glEnd();
}