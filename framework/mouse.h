#ifndef MOUSE_H
#define MOUSE_H

#include "GLHeaders.h"

class Mouse;

static Mouse* glMouse;

class Mouse {
public:
	Mouse();
	~Mouse();
	void resetMouseEvents();

	int getMouseX();
	int getMouseY();

	bool isRightMousePressed();
	bool isLeftMousePressed();
	bool isMiddleMousePressed(); 
	bool onRightMouseUp();
	bool onLeftMouseUp();
	bool onMiddleMouseUp();
	bool onRightMouseDown();
	bool onLeftMouseDown();
	bool onMiddleMouseDown();
private:
	static void mouseButtonsHandler(int button, int state, int x, int y);
	static void mouseMoveHandler(int x, int y);
	static void mouseDragHandler(int x, int y);
private:
	int mouseX = 0;
	int mouseY = 0;

	bool leftMousePressed = false;
	bool rightMousePressed = false;
	bool middleMousePressed = false;

	bool leftMouseDown = false;
	bool rightMouseDown = false;
	bool middleMouseDown = false;

	bool leftMouseUp = false;
	bool rightMouseUp = false;
	bool middleMouseUp = false;
};

#endif