#include "collisions.h"

void collisionReaction(vec3* pos1, vec3* vel1, vec3* pos2, vec3* vel2, float collisionDepth) {
    vec3 collisionNormal = normalize(*pos2 - *pos1);
    float initVel1 = dot(*vel1, collisionNormal);
    float initVel2 = dot(*vel2, collisionNormal);

    float mass1 = 1.0f;
    float mass2 = 1.0f;
    float finalVel1 = (mass1 - mass2) / (mass1 + mass2) * initVel1 + 2.0f * mass2 / (mass1 + mass2) * initVel2;
    float finalVel2 = 2.0f * mass1 / (mass1 + mass2) * initVel1 + (mass2 - mass1) / (mass1 + mass2) * initVel2;

    *pos1 += (collisionDepth / 2.0f) * collisionNormal;
    *pos2 -= (collisionDepth / 2.0f) * collisionNormal;

    *vel1 = (*vel1 - vec3(initVel1) * collisionNormal) + vec3(finalVel1) * collisionNormal;
    *vel2 = (*vel2 - vec3(initVel2) * collisionNormal) + vec3(finalVel2) * collisionNormal;
}

void collisionReactionStatic(vec3* pos, vec3* vel, vec3 staticPos, float collisionDepth) {
    vec3 collisionNormal = normalize(staticPos - *pos);
    *pos += collisionDepth * collisionNormal;
    *vel = reflect(*vel, collisionNormal);
}

void sphereCollisionReactionStatic(vec2* pos, vec2* vel, vec2 staticPos, float collisionDepth) {
    vec2 collisionNormal = normalize(staticPos - *pos);
    *pos += collisionDepth * collisionNormal;
    *vel = reflect(*vel, collisionNormal);
}

void collisionReactionStatic(vec2* pos, vec2* vel, vec2 staticPos, vec2 collisionNormal) {
    *vel = reflect(*vel, collisionNormal);
}

//Determines if two balls are colliding or not
bool spheresColliding(vec3 pos1, vec3 pos2, float* collisionDepth) {
    *collisionDepth = Maths::distBetween(pos1, pos2) - 2.0f;
    return *collisionDepth < 0.0f;
}

bool circleCollidingVertex(vec2 cPos, float cRadius, vec2 v, vec2* collisionNormal) {
    //Get the vector from the vertex to the circle
    vec2 vecBetween = cPos - v;
    //Get the distance between the circle centre and the vertex
    float dist = length(vecBetween);

    //Determine if they are colliding
    if(dist < cRadius) {
        //Determine the collision normal
        *collisionNormal = normalize(vecBetween);
        //Return that a collision has occured
        return true;
    }

    //Return that no collision has occured
    return false;
}

bool circleCollidingLine(vec2 cPos, float cRadius, vec2 l1, vec2 l2, vec2 normal, vec2* collisionNormal) {
    //Gets the midpoint of the line segment
    vec2 midPoint = l1 + (0.5f * (l2 - l1));
    //Gets the vector from the midpoint of the line to the centre of the circle
    vec2 midToCircle = cPos - midPoint;
    //Gets the length of the line segment
    float lineSegLength = length(l2 - l1);
    //Projects the to circle vector across the surface normal
    vec2 normProjection = proj(midToCircle, normal);
    float distFromLine = length(normProjection);
    //Projects the to circle vector across the line segment
    vec2 vecProjection = proj(midToCircle, l2 - l1);
    float distFromMid = length(vecProjection);

    //If the circle centre is one the same plane as the line segment
    if(distFromMid < lineSegLength / 2.0f) {
        
        //If the distance from the line is less than the radius of the circle
        if(distFromLine < cRadius) { 
            //The collision normal will be the surface's normal
            *collisionNormal = normal;
            //A collision has occured
            return true;
        }

        //If it is not close enough, there is no collsion
        return false;
    }else {
        //The only way the circle can collide with the line outside the plane,
        //is if it collides with one of the vertices
        return circleCollidingVertex(cPos, cRadius, l1, collisionNormal) ||
                circleCollidingVertex(cPos, cRadius, l2, collisionNormal);
    }
}

//Determines if a circle is colliding with a polygon
bool circleCollidingPoly(vec2 cPos, float cRadius, vec2 posOffset, float rotZ, vector<vec2> vertices, vector<vec2> normals, vec2* collisionNormal) {
    //Iterate through each of the polygons vertices
    for(int i = 0; i < vertices.size() - 1; i++) {
        //Translate and Rotate the input vertices
        vec2 v1 = rotate(vertices[i], radians(rotZ)) + posOffset;
        vec2 v2 = rotate(vertices[i + 1], radians(rotZ)) + posOffset;
        vec2 normal = rotate(normals[i], radians(rotZ));
        //If the circle is colliding with this edge of the polygon
        if(circleCollidingLine(cPos, cRadius, v1, v2, normal, collisionNormal))
            //Then there is a collision occuring
            return true;
    }

    return false;
}