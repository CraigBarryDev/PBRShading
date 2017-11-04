#include "mouse.h"

Mouse::Mouse() {
	//Set the global mouse to this item
	glMouse = this;

	//Initialize mouse x and y to 0
	glMouse->mouseX = 0;
	glMouse->mouseY = 0;
	//Initialize all mouse button to not pressed
	glMouse->leftMousePressed = false;
	glMouse->rightMousePressed = false;
	glMouse->middleMousePressed = false;

	//Set callbacks
	glutPassiveMotionFunc(mouseMoveHandler);
	glutMouseFunc(mouseButtonsHandler);
	glutMotionFunc(mouseDragHandler);

	//Reset the mouse events
	resetMouseEvents();
}

Mouse::~Mouse() {}

void Mouse::resetMouseEvents() {
	glMouse->leftMouseDown = false;
	glMouse->rightMouseDown = false;
	glMouse->middleMouseDown = false;

	glMouse->leftMouseUp = false;
	glMouse->rightMouseUp = false;
	glMouse->middleMouseUp = false;
}

void Mouse::mouseButtonsHandler(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		glMouse->leftMousePressed = true;
		glMouse->leftMouseDown = true;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		glMouse->rightMousePressed = true;
		glMouse->rightMouseDown = true;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		glMouse->middleMousePressed = true;
		glMouse->middleMouseDown = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)  {
		glMouse->leftMousePressed = false;
		glMouse->leftMouseUp = true;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		glMouse->rightMousePressed = false;
		glMouse->rightMouseUp = true;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
		glMouse->middleMousePressed = false;
		glMouse->middleMouseUp = true;
	}
}

void Mouse::mouseMoveHandler(int x, int y) {
	glMouse->mouseX = x;
	glMouse->mouseY = y;
}

void Mouse::mouseDragHandler(int x, int y) {
	mouseMoveHandler(x, y);
}

int Mouse::getMouseX() {return glMouse->mouseX;}
int Mouse::getMouseY() {return glMouse->mouseY;}
bool Mouse::isRightMousePressed() {return glMouse->rightMousePressed;}
bool Mouse::isLeftMousePressed() {return glMouse->leftMousePressed;}
bool Mouse::isMiddleMousePressed() {return glMouse->middleMousePressed;}
bool Mouse::onRightMouseUp() {return glMouse->rightMouseUp;}
bool Mouse::onLeftMouseUp() {return glMouse->leftMouseUp;}
bool Mouse::onMiddleMouseUp() {return glMouse->middleMouseUp;}
bool Mouse::onRightMouseDown() {return glMouse->rightMouseDown;}
bool Mouse::onLeftMouseDown() {return glMouse->leftMouseDown;}
bool Mouse::onMiddleMouseDown() {return glMouse->middleMouseDown;}