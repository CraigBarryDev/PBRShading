#ifndef N_SIDED_POLY_H
#define N_SIDED_POLY_H

#include <vector>
#include "framework/GLHeaders.h"

class NSidedPolygon {
public:
	NSidedPolygon();
    NSidedPolygon(unsigned int nSides, float depth, float radius);

    const int getNSides() { return nSides; }
private:
    void addVec(vector<GLfloat>* list, const vec3& vec);
    void addVec(vector<GLfloat>* list, const vec2& vec);
public:
    vector<GLfloat> vertices;
    vector<GLfloat> texCoords;
    vector<GLfloat> normals;

    vector<vec2> vertices2D;
    vector<vec2> normals2D;
private:
	int nSides;
};

#endif