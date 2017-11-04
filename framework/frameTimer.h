#ifndef FRAMETIMER_H
#define FRAMETIMER_H

#include "GLHeaders.h"

static float frameTime = 0.0;
static float currFPS = 0.0;

float getTimeSec();
float getTimeMS();
float getFrameTime();

float getFPS();
void printFPS();
void updateFrameTime();

#endif
