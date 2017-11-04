#include "sphere.h"

Sphere::Sphere() {}

Sphere::Sphere(int stacks, int slices, float radius) {
	//Init sphere coordinate vectors
	vertices.clear();
	normals.clear();
	texCoords.clear();
	indices.clear();

	//The angle covered by a given stack from the middle
	// float sliceAngle = 180.0;
	float currSliceAngle = 0.0f;

	for(unsigned int j = 0; j <= stacks; j++) {
		for (unsigned int i = 0; i <= slices; i++) {
			//Determine the angle from the centre of the circle
			float theta = (float)((float)i / (float)(slices)) * (2.0f * 3.1419f);
			float currSliceAngle = (float)((float)j / (float)(stacks)) * (3.1419f);
			//Generate the points of the circle based on the radius and angle from the centre
			float x = radius * cosf(theta) * sinf(currSliceAngle);
			float y = radius * cosf(currSliceAngle);
			float z = radius * sinf(theta) * sinf(currSliceAngle);
			//Add the xyz coordinates to the points array
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			//Calculate the surface normal
			vec3 normal = normalize(vec3(x,y,z));
			//Add normals to coordinates arrays
			normals.push_back(normal.x);
			normals.push_back(normal.y);
			normals.push_back(normal.z);

			//Calculate texture coordinates
			texCoords.push_back((float)(slices - i) / (float)(slices));
			texCoords.push_back((float)(stacks - j) / (float)(stacks));
		}
	}

	for(unsigned int j = 0; j < stacks; j++) {
		for (unsigned int i = 0; i < slices; i++) {
			indices.push_back(i + 1 + (j * (slices + 1)));
			indices.push_back(i + 1 + ((j + 1) * (slices + 1)));
			indices.push_back(i + (j * (slices + 1)));
	
			indices.push_back(i + ((j + 1) * (slices + 1)));
			indices.push_back(i + (j * (slices + 1)));
			indices.push_back(i + 1 + ((j + 1) * (slices + 1)));
		}
	}
}

Sphere::~Sphere() {}