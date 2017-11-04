#include "Entity.h"
#include "../maths.h"
#include "../frameTimer.h"

Entity::Entity() {}

Entity::Entity(TexturedModel* model) {
	initEntity(model, vec3(0.0f), vec3(0.0f), 1.0f);
}

Entity::Entity(TexturedModel* model, vec3 pos = vec3(0.0f), vec3 rot = vec3(0.0f), float scale = 1.0f) {
	initEntity(model, pos, rot, scale);
}

void Entity::cleanUp() {
	//Delete the memory allocated by the raw model
	delete model->getRawModel();
}

void Entity::update() {
	if(destroyed){
		timeDestroyed += getFrameTime();
	}
}

void Entity::initEntity(TexturedModel* model, vec3 pos, vec3 rot, float scale) {
	this->model = model;
	this->pos = pos;
	this->rot = rot;
	this->scale = scale;
}

mat4 Entity::getTransformationMatrix() {
	return Maths::createTransformMat(pos, rot, scale);
}

vec2 Entity::getTextureOffset() {
	const int nRows = model->getTexture()->getTextureAtlasSizeX();
	const int nCols = model->getTexture()->getTextureAtlasSizeY();
	return vec2((float)((float)(textureIndex % nCols) / (float)nCols),
		(float)(textureIndex / nCols) / (float)nRows);
}

void Entity::increaseRotation(float rx, float ry, float rz) {
	rot.x += rx;
	rot.y += ry;
	rot.z += rz;
}