#include "glGraphics.h"

static int windowID = 0;

int main(int argc, char **argv)
{
	time_t t;
	//Seed random numbers
	srand((unsigned)time(NULL));

	//Initialize OpenGL
	initGL(argc, argv);

	return EXIT_SUCCESS;
}

static void initGlut(int argc, char** argv) {
	//Initializes GLUT
	glutInit(&argc, argv);

	//Sets parameters for glut window
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(100, 100);

	//Set context to version 3.3 core
	glutInitContextVersion (3, 3);
	glutInitContextFlags (GLUT_FORWARD_COMPATIBLE);
	//Creates window
	windowID = glutCreateWindow("GLUT Window");

	//Setup the projection matrix
	setupProjection();
}

static void windowResize(int width, int height) {
	//Updates the size of the window
	windowWidth = width;
	windowHeight = height;
	//Resets the projection matrix with appropriate aspect ratios
	setupProjection();

	//Sets the rendering area of the window to the entire window
	glViewport(0, 0, windowWidth, windowHeight);
}

static void setupProjection() {
	
}

static void glUpdate(void) {
	GLenum err;
	//Print OpenGL errors
    while ((err = glGetError()) != GL_NO_ERROR) {
        printf("OpenGL error: %s\n", gluErrorString(err));
	}

	const static int ESCAPE_KEY = 27;
	//If Escape pressed, end application
	if (keys->keyUpEvent(ESCAPE_KEY)) {
		glClose();
		return;
	}

	//Updates the frame timer
	updateFrameTime();

	//Call main update function
	update();

	//Update the camera's values position
	cam.updateCamera();

	//Forces the display to update
	glutPostRedisplay();

	//Reset key up and key down events
	keys->resetKeyEvents();
	//Reset mouse up and mouse down events
	mouse->resetMouseEvents();
}

static void glClose() {
	//CLeanup keyboard
	delete keys;
	//Cleanup mouse
	delete mouse;
	//Cleanup model loader (deletes vaos and vbos)
	loader.cleanUp();

	//Calls user function to cleanup any allocated memory
	cleanUp();

	//Destroys the window
	glutDestroyWindow(windowID);
}

static void glDisplay(void) {
	//Clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Call main display function
	display();

	//Swap buffers
	glutSwapBuffers();
}

void initGL(int argc, char** argv) {
	initGlut(argc, argv);

	//Sets clear color to black
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_DEPTH_TEST);

	//Set glut callbacks
	glutDisplayFunc(glDisplay);
	glutIdleFunc(glUpdate);
	glutReshapeFunc(windowResize);

	//Initialize keyboard
	keys = new Keyboard();
	mouse = new Mouse();

	//Calls user defined init function
	init();

	//Starts the rendering loop
	glutMainLoop();
}
