#include "cylinder.h"

Cylinder::Cylinder() {}
Cylinder::~Cylinder() {}

Cylinder::Cylinder(int stacks, int slices, float radius) {
	//Init cylinder coordinate vectors
	vertices.clear();
	normals.clear();
	indices.clear();
	texCoords.clear();

	for(unsigned int j = 0; j <= stacks; j++) {
		for (unsigned int i = 0; i <= slices; i++) {
			//Determine the angle from the centre of the circle
			float theta = (float)((float)i / (float)(slices)) * (2.0f * 3.1419f);

			//Generate the points of the circle based on the radius and angle from the centre
			float x = radius * cosf(theta);
			float y = (((float)j / (float)stacks) - 0.5f) * (radius * 2.0f);
			float z = radius * sinf(theta);
			//Add the xyz coordinates to the points array
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			//Calculate the surface normal
			glm::vec3 normal = glm::normalize(glm::vec3(x,0.0f,z));
			//Add normals to coordinates arrays
			normals.push_back(normal.x);
			normals.push_back(normal.y);
			normals.push_back(normal.z);

			//Set texture coordinates
			texCoords.push_back((float)i / (float)slices);
			texCoords.push_back((float)j / (float)stacks);
		}
	}

	for(unsigned int j = 0; j < stacks; j++) {
		for (unsigned int i = 0; i < slices; i++) {
			//Set indicies
	 		indices.push_back(i + (j * (slices + 1)));
			indices.push_back(i + 1 + ((j + 1) * (slices + 1)));
			indices.push_back(i + 1 + (j * (slices + 1)));
	
			indices.push_back(i + 1 + ((j + 1) * (slices + 1)));
			indices.push_back(i + (j * (slices + 1)));
			indices.push_back(i + ((j + 1) * (slices + 1)));
		}
	}

	//Add cylinder's top and bottom
	addCylinderCap(radius, slices, true);
	addCylinderCap(radius, slices, false);
}

void Cylinder::addCylinderCap(float radius, int slices, bool top) {
	int nVertices = vertices.size() / 3;

	vertices.push_back(0.0f);
	vertices.push_back(top ? radius : -radius);
	vertices.push_back(0.0f);
	normals.push_back(0.0f);
	normals.push_back(top ? 1.0f : -1.0f);
	normals.push_back(0.0f);
	texCoords.push_back(top ? 1.0f : 0.0f);
	texCoords.push_back(top ? 1.0f : 0.0f);
		
	for (unsigned int i = 0; i <= slices; i++) {
		//Determine the angle from the centre of the circle
		float theta = (float)((float)i / (float)(slices)) * (2.0f * 3.1419f);
		//Generate the points of the circle based on the redius and angle from the centre
		float x = radius * cosf(theta);
		float y = top ? radius : -radius;
		float z = radius * sinf(theta);
		//Add the xyz coordinates to the points array
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);

		//Add normals to coordinates arrays
		normals.push_back(0.0f);
		normals.push_back(top ? 1.0f : -1.0f);
		normals.push_back(0.0f);

		//Set texture coordinates
		texCoords.push_back(top ? 1.0f : 0.0f);
		texCoords.push_back(top ? 1.0f : 0.0f);
	}

	for (unsigned int i = 0; i < slices; i++) {
		//Set indicies
		if(top) {
			indices.push_back(i + nVertices + 2);
	 		indices.push_back(i + nVertices + 1);
			indices.push_back(nVertices);
		}else {
			indices.push_back(nVertices);
	 		indices.push_back(i + nVertices + 1);
			indices.push_back(i + nVertices + 2);
		}
		
	}
}