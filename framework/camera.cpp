#include "camera.h"

Camera cam;

Camera::Camera() {
	lastX = 0;
	lastY = 0;
	rotX = 0.0f;
	rotY = 0.0f;
	scale = 1.0f;
	sensitivity = 1.0f;
	control = inactive;
}

Camera::~Camera() {}

void Camera::rotateWMouse(float sensitivity) {
	control = rotateCam;
}

void Camera::panWMouse(float sensitivity) {
	control = pan;
}

void Camera::zoomWMouse(float sensitivity) {
	control = zoom;
}

void Camera::stopMouseControl() {
	control = inactive;
}

void Camera::updateCamera() {
	int x = glMouse->getMouseX();
	int y = glMouse->getMouseY();
    float dx, dy;

    if(control == inactive) {
    	lastX = x;
    	lastY = y;
    }else {
    	dx = (x - lastX) * sensitivity;
		dy = (y - lastY) * sensitivity;
		lastX = x;
		lastY = y;

		switch (control) {
		case rotateCam:
			rotX += dy;
			rotY += dx;
			break;
		case pan:
			break;
		case zoom:
			scale += dy / 100.0;
			break;
		}
    }
}

glm::mat4 Camera::genViewMatrix() {
	glm::mat4 viewMatrix(1.0f);
	//Rotate the view matrix
	viewMatrix = glm::rotate(viewMatrix, rotX * glm::pi<float>() / 180.0f, glm::vec3(1.0, 0.0, 0.0));
	viewMatrix = glm::rotate(viewMatrix, rotY * glm::pi<float>() / 180.0f, glm::vec3(0.0, 1.0, 0.0));
	//Scale the view matrix
	viewMatrix = glm::scale(viewMatrix, glm::vec3(scale));
	//Return the camera's view matrix
	return viewMatrix;
}

glm::mat3 Camera::genNormalMatrix() {
	return glm::transpose(glm::inverse(glm::mat3(genViewMatrix())));
}

glm::mat3 Camera::genNormalMatrix(glm::mat3 viewMatrix) {
	return glm::transpose(glm::inverse(viewMatrix));

}