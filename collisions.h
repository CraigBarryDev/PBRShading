#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "framework/GLHeaders.h"
#include "framework/maths.h"

void collisionReaction(vec3* pos1, vec3* vel1, vec3* pos2, vec3* vel2, float collisionDepth);
void collisionReactionStatic(vec3* pos, vec3* vel, vec3 staticPos, float collisionDepth);
void sphereCollisionReactionStatic(vec2* pos, vec2* vel, vec2 staticPos, float collisionDepth);
void collisionReactionStatic(vec2* pos, vec2* vel, vec2 staticPos, vec2 collisionNormal);
//Determines if two balls are colliding or not
bool spheresColliding(vec3 pos1, vec3 pos2, float* collisionDepth);

bool circleCollidingVertex(vec2 cPos, float cRadius, vec2 v, vec2* collisionNormal);
bool circleCollidingLine(vec2 cPos, float cRadius, vec2 l1, vec2 l2, vec2 normal, vec2* collisionNormal);
//Determines if a circle is colliding with a polygon
bool circleCollidingPoly(vec2 cPos, float cRadius, vec2 posOffset, float rotZ, vector<vec2> vertices, vector<vec2> normals, vec2* collisionNormal);

#endif