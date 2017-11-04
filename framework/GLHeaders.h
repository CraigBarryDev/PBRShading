#ifndef GLHEADERS_H
#define GLHEADERS_H

#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <vector>

//Get the OpenGL function prototypes for core profile functions
#define GL_GLEXT_PROTOTYPES
//Forces GLM to use radians
#define GLM_FORCE_RADIANS
//Allows use of vector projections and vector rotations
#define GLM_ENABLE_EXPERIMENTAL

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
//Using freeglut so that a core profile can be set
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/projection.hpp>
#include <glm/gtx/rotate_vector.hpp>


#include "SOIL.h"

using namespace std;
using namespace glm;

#endif