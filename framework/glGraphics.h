#ifndef GL_GRAPHICS_H
#define GL_GRAPHICS_H

#include "utils.h"
#include "keyboard.h"
#include "mouse.h"
#include "camera.h"
#include "frameTimer.h"
#include "loader.h"

extern void update(void);
extern void display(void);
extern void init(void);
extern void cleanUp(void);

static void initGlut(int argc, char** argv);
static void windowResize(int width, int height);
static void setupProjection();
static void updateCamera();
static void glUpdate();
static void glDisplay();
static void glClose();

void initGL(int argc, char** argv);

Keyboard* keys;
Mouse* mouse;
Loader loader;

#endif