#include "RawModel.h"

RawModel::RawModel(GLuint vaoID, unsigned int vertexCount, GLfloat radius) :
	vaoID(vaoID),
	vertexCount(vertexCount),
	radius(radius),
	indices(true)
{}

RawModel::RawModel(GLuint vaoID, unsigned int vertexCount, GLfloat radius, bool hasIndices) :
	vaoID(vaoID),
	vertexCount(vertexCount),
	radius(radius),
	indices(hasIndices)
{}
