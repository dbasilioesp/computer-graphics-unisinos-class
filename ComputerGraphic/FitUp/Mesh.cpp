#include "Mesh.h"


Mesh* ReadMeshObject(string filename)
{

	Mesh *mesh = new Mesh;
	Vertex *vertex;
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
			
				Face face;
			
				while(lineStream >> token){
					
					size_t found = token.find("//");
					
					if(found != string::npos){
						istringstream aux(token.substr(0, found));
						aux >> vertexReference;
						face.vertexIndices.push_back(vertexReference - 1);
					} else {
						istringstream aux(token);
						aux >> vertexReference;
						face.vertexIndices.push_back(vertexReference - 1);
					}
				
				}
			
				mesh->faces.push_back(face);
			}
		}

	}
	
	
	infile.close();

	return mesh;
}
