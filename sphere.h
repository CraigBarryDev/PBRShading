#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include "framework/GLHeaders.h"

class Sphere {
public:
	Sphere();
	Sphere(int stacks, int slices, float radius);
	~Sphere();

public:
	vector<GLfloat> vertices;
	vector<GLfloat> normals;
	vector<GLfloat> texCoords;
	vector<GLuint> indices;
};


#endif