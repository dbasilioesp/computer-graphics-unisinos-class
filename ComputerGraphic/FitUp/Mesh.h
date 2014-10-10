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

	if(!infile.is_open()){
		perror(filename.c_str());
	}
	

	while(!infile.eof()){
		
		getline(infile, line, '\n');
		istringstream lineStream(line);

		while(lineStream >> token){

			if(token == "#") continue;
			if(token == "vn") continue;
			if(token == "newmtl") continue;
			if(token == "d") continue;
			if(token == "Ns") continue;
			if(token == "Ka") continue;
			if(token == "Kd") continue;
			if(token == "Ks") continue;

			if(token == "v"){

				float x, y, z;
				Vertex vertex;
				
				lineStream >> x;
				lineStream >> y;
				lineStream >> z;

				vertex.axis[0] = x;
				vertex.axis[1] = y;
				vertex.axis[2] = z;

				mesh->vertexes.push_back(vertex);
			}
			
			if(token == "f"){
			
				Polygon polygon;
			
				while(lineStream >> token){
					
					size_t found = token.find("//");
					
					if(found != string::npos){
						istringstream aux(token.substr(0, found));
						aux >> vertexReference;
						polygon.vertexes.push_back(vertexReference - 1);
					} else {
						istringstream aux(token);
						aux >> vertexReference;
						polygon.vertexes.push_back(vertexReference - 1);
					}
				
				}
			
				mesh->polygons.push_back(polygon);
			}
		}

	}
	
	
	infile.close();

	return mesh;
}
