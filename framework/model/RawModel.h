#pragma once

#include "../GLHeaders.h"

class RawModel {
public:
	RawModel(GLuint vaoID, unsigned int vertexCount, GLfloat radius);
	RawModel(GLuint vaoID, unsigned int vertexCount, GLfloat radius, bool hasIndices);
	const GLuint getVAOID() {return vaoID;}
	const unsigned int getVertexCount() {return vertexCount;}
	const float getModelRadius() { return radius; }
	const bool hasIndices() { return indices; } 
private:
	GLuint vaoID;
	unsigned int vertexCount;
	float radius;
	bool indices;
};