#ifndef MATHS_H
#define MATHS_H

#include "GLHeaders.h"

class Maths {
public:
	//Makes the class uninstansiable
	virtual ~Maths() = 0;

	//Takes in a plane (p1,p2,p3 defines a plane) and then a 2D x,z position on the plane
	//And works out out its height on the terrain by interpolating the heights of each corner of the plane
	static float barryCentricInterpolation(vec3 p1, vec3 p2, vec3 p3, vec2 pos) {
		float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
		float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
		float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
		float l3 = 1.0f - l1 - l2;
		return l1 * p1.y + l2 * p2.y + l3 * p3.y;
	}


	static mat4 createTransformMat(vec3 trans, quat rot, vec3 scale) {
		//Rotation using quaternions (still has gimbal lock on z-axis,
		//but is more efficient then vector/matrix rotations)
		mat4 m(1.0f);
		m = glm::translate(m, trans);
		m = m * mat4_cast(rot);
		m = glm::scale(m, scale);
		return m;
	}

	static mat4 createTransformMat(vec3 trans, quat rot, float scale = 1.0f) {
		//Rotation using quaternions (still has gimbal lock on z-axis,
		//but is more efficient then vector/matrix rotations)
		mat4 m(1.0f);
		m = glm::translate(m, trans);
		m = m * mat4_cast(rot);
		m = glm::scale(m, vec3(scale));
		return m;
	}

	static mat4 createTransformMat(vec3 trans, vec3 rot, float scale = 1.0f) {
		//Rotation using quaternions (still has gimbal lock on z-axis,
		//but is more efficient then vector/matrix rotations)
		mat4 m(1.0f);
		m = glm::translate(m, trans);
		rot = glm::radians(vec3(rot));
		glm::quat rotationQuat = quat(rot);
		m = m * mat4_cast(rotationQuat);
		m = glm::scale(m, vec3(scale));
		return m;
	}

	static mat4 createProjectionMatrix(float width, float height, float fov, float nearPlane, float farPlane) {
		//Get the aspect ratio of the screen (this will make sure that square objects actually appear square
		//and not skewed by the size of shape of the display)
		const float aspectRatio = width / height;
		//Create the projection matrix
		return  glm::perspective(radians(fov), aspectRatio, nearPlane, farPlane);
	}

	static mat4 createViewMatrix(float rx, float ry, vec3 camPos) {
		mat4 v(1.0f);

		//Rotate the camera first and then translate it (this way you will move in the direction the camera is facing)
		/*quat r = normalize(quat(radians(cam->getRotation())));
		mat4 v = mat4_cast(r);*/
		v = rotate(v, radians(rx), vec3(1.0f, 0.0f, 0.0f));
		v = rotate(v, radians(ry), vec3(0.0f, 1.0f, 0.0f));

		//Translate the matrix (translate the reverse of the camera position, this way the world will move opposite to the camera)
		v = translate(v, -camPos);
		
		//Return the view matrix
		return v;
	}

	//min is inclusive, max is exclusive
	static int randBetween(int min, int max) {
		//If values wrong way round, swap them
		if(min > max) {
			int temp = min;
			min = max;
			max = temp;
		}
		//Return random between given values
		return (rand() % (max - min)) + min;
	}

	static float randBetweenf(float min, float max) {
		//If values wrong way round, swap them
		if(min > max) {
			float temp = min;
			min = max;
			max = temp;
		}
		//Return random between 0 and 1
		float rand1 = (float)rand() / (float)RAND_MAX;
		//Returns random between given values
		return (rand1 * (max - min)) + min;
	}

	//Get the distance between two 3D points
	static float distBetween(vec3 v1, vec3 v2) {
		vec3 dv = v2 - v1;
		return length(dv);
	}

	//Get the distance between two 2D points
	static float distBetween(vec2 v1, vec2 v2) {
		vec2 dv = v2 - v1;
		return length(dv);
	}

	//Vertices should be specified in counter-clockwise winding order
	//Gets the vector that is perpindicular to the plane
	static vec3 getPlaneNormal(vec3 v1, vec3 v2, vec3 v3) {
		//Get vectors from v2 to other points
		vec3 a1 = v1 - v2;
		vec3 a2 = v3 - v2;

		return normalize(cross(a2, a1));
	}
};

#endif