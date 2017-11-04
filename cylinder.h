#ifndef CYLINDER_H
#define CYLINDER_H

#include "framework/GLHeaders.h"
#include <vector>

class Cylinder {
public:
	Cylinder();
	Cylinder(int stacks, int slices, float radius);
	~Cylinder();
private:
	void addCylinderCap(float radius, int slices, bool top);

public:
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texCoords;
	std::vector<GLuint> indices;
};

#endif
