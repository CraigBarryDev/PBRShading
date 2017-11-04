#ifndef CAMERA_H
#define CAMERA_H

#include "GLHeaders.h"
#include "mouse.h"

typedef enum { inactive, rotateCam, pan, zoom } CameraControl;

class Camera {
public:
	Camera();
	~Camera();

public:
	//Generates the view matrix based on the camera's position
	glm::mat4 genViewMatrix();
	//Generate the normal matrix by first generating the view matrix
	glm::mat3 genNormalMatrix();
	//Generates the normal matrix with a pre-generated view matrix for efficiency
	glm::mat3 genNormalMatrix(glm::mat3 viewMatrix);
	//Sets the camera to rotate with the mouse
	void rotateWMouse(float sensitivity);
	//Sets the camera to zoom with the mouse
	void zoomWMouse(float sensitivity);
	//Sets the camera to pan with the mouse
	void panWMouse(float sensitivity);
	//Stops the camera being controlled by the mouse
	void stopMouseControl();
	//Updates the camera to move with mouse controls
	void updateCamera();

	//Get the rotation values of the camera
	const float getRotX() {return rotX;}
	const float getRotY() {return rotY;}
	const float getScale() {return scale;}
private:
	int lastX, lastY;
	float rotX, rotY;
	float scale;
	float sensitivity;
	CameraControl control;
};

extern Camera cam;

#endif