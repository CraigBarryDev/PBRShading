#include "nSidedPolygon.h"

NSidedPolygon::NSidedPolygon() 
{}

NSidedPolygon::NSidedPolygon(unsigned int nSides, float depth, float radius)
	:
nSides(nSides)
{
    float z1 = depth / 2.0f;
    float z2 = -depth / 2.0f;
    int startingIndex = 0;

    //The difference
    float dtheta = radians(1.0f / nSides * 360.0f);

    //Iterate through the sides of the face
    for(int i = 0; i < nSides; i++) {
        float theta1 = radians((float)i / (float)nSides * 360.0f);
        float theta2 = theta1 + dtheta;
        float x1 = radius * cosf(theta1);
        float x2 = radius * cosf(theta2);
        float y1 = radius * sinf(theta1);
        float y2 = radius * sinf(theta2);

        addVec(&vertices, vec3(0.0f, 0.0f, z1));
        addVec(&vertices, vec3(x1,y1,z1));
        addVec(&vertices, vec3(x2,y2,z1));
        addVec(&normals, vec3(0.0f, 0.0f, 1.0f));
        addVec(&normals, vec3(0.0f, 0.0f, 1.0f));
        addVec(&normals, vec3(0.0f, 0.0f, 1.0f));
        addVec(&texCoords, vec2(0.5f, 0.5f));
        addVec(&texCoords, vec2(0.0f, 0.0f));
        addVec(&texCoords, vec2(0.0f, 0.0f));

        addVec(&vertices, vec3(0.0f, 0.0f, z2));
        addVec(&vertices, vec3(x1,y1,z2));
        addVec(&vertices, vec3(x2,y2,z2));     
        addVec(&normals, vec3(0.0f, 0.0f, -1.0f));
        addVec(&normals, vec3(0.0f, 0.0f, -1.0f));
        addVec(&normals, vec3(0.0f, 0.0f, -1.0f));
        addVec(&texCoords, vec2(0.5f, 0.5f));
        addVec(&texCoords, vec2(0.0f, 0.0f));
        addVec(&texCoords, vec2(0.0f, 0.0f));

        //The normal of the face connection the end faces on this given edge
        vec3 normal = normalize(vec3(x1,y1,0.0f) + vec3(x2,y2,0.0f));
        addVec(&vertices, vec3(x1,y1,z2));
        addVec(&vertices, vec3(x1,y1,z1));
        addVec(&vertices, vec3(x2,y2,z1));     
        addVec(&normals, normal);
        addVec(&normals, normal);
        addVec(&normals, normal);
        addVec(&texCoords, vec2(0.0f, 0.0f));
        addVec(&texCoords, vec2(0.0f, 0.0f));
        addVec(&texCoords, vec2(0.0f, 0.0f));

        addVec(&vertices, vec3(x2,y2,z2));
        addVec(&vertices, vec3(x1,y1,z2));
        addVec(&vertices, vec3(x2,y2,z1));     
        addVec(&normals, normal);
        addVec(&normals, normal);
        addVec(&normals, normal);
        addVec(&texCoords, vec2(0.0f, 0.0f));
        addVec(&texCoords, vec2(0.0f, 0.0f));
        addVec(&texCoords, vec2(0.0f, 0.0f));

        //Add 2D vertices and normals for collision detections
        vertices2D.push_back(vec2(x1,y1));
        if(i != nSides -1) normals2D.push_back(vec2(normal.x, normal.y));
    }
}

void NSidedPolygon::addVec(vector<GLfloat>* list, const vec3& vec) {
    list->push_back(vec.x);
    list->push_back(vec.y);
    list->push_back(vec.z);
}

void NSidedPolygon::addVec(vector<GLfloat>* list, const vec2& vec) {
    list->push_back(vec.x);
    list->push_back(vec.y);
}