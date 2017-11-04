#ifndef MAIN_H
#define MAIN_H

#include "backdrop.h"
#include "cannon.h"
#include "collisions.h"
#include "nSidedPolygon.h"
#include "sphere.h"
#include "particles.h"
#include "peg.h"

#include "framework/shaders/StaticShader.h"
#include "framework/EntityRenderer.h"
#include "framework.h"

#define GAME_Z -35.0f

#define CANNON_SENSITIVITY 50.0f
#define MAX_CANNON_ROTATION 85.0f
#define MIN_CANNON_ROTATION -85.0f

#define GRAVITY_CONST 9.8f

#define LIGHT_COLOR vec3(1.0f, 1.0f, 1.0f)
#define LIGHT_POS vec3(-2.0f, 2.0f, -15.0f)
#define LIGHT_AMBIENT vec3(0.4f)

#define BALL_SPEED 5.0f   
#define BALL_SIZE 0.9f

void addCannonBall(vec3 pos, vec3 vel);
void addPeg(vec3 pos, vec3 angularVeloc);
void clearBalls();
void clearPegs();
void setupLevel();
void printControls();

void handleMouse();
void handleKeyboard();

void cleanUpModels();
void cleanUpShaders();
void cleanUpTextures();

void initModels();
void initShaders();
void initTextures();
void initRenderer();

static Loader* loader;
extern EntityRenderer renderer;

//Entity Lists
extern std::vector<Entity*> ballEntities;
extern unordered_map<GLuint, vector<Entity*>*> entities;

//Shaders
extern StaticShader staticShader;

//Textures
extern ModelTexture* ballTexture;
extern ModelTexture* woodTexture;
extern ModelTexture* cannonTexture;
extern ModelTexture* blueTexture;
extern ModelTexture* greenTexture;
extern ModelTexture* orangeTexture;
extern ModelTexture* particleTexture;

//Models
extern TexturedModel* ballTexModel;

#endif