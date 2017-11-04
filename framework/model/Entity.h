#ifndef ENTITY_H
#define ENTITY_H

#include "TexturedModel.h"
#include "../GLHeaders.h"

class Entity {
public:
	Entity();
	Entity(TexturedModel* model);
	Entity(TexturedModel* model, vec3 pos, vec3 rot, float scale);
	void cleanUp();
	void update();

	//Getters
	TexturedModel* getModel() { return model; }
	const vec3 getPosition() { return pos; }
	const float getPosX() { return pos.x; }
	const float getPosY() { return pos.y; }
	const float getPosZ() { return pos.z; }
	const float getRotX() { return rot.x; }
	const float getRotY() { return rot.y;}
	const float getRotZ() { return rot.z; }
	const vec3 getRotation() { return rot; }
	const float getScale() { return scale; }
	const float getRadius() { return model->getRawModel()->getModelRadius() * scale; }
	const bool getDestroyed() { return destroyed; }
	const float getTimeDestroyed() { return timeDestroyed; }
	const bool shouldBeDisposed() { return timeDestroyed > 1.0f; }
	vec2 getTextureOffset();
	mat4 getTransformationMatrix();

	//Setters
	void setModel(TexturedModel* model) { this->model = model;  }
	void setPosition(vec3 pos) { this->pos = pos; }
	void setPosX(float x) { this->pos.x = x; }
	void setPosY(float y) { this->pos.y = y; }
	void setPosZ(float z) { this->pos.z = z; }
	void setRotation(vec3 rot) { this->rot = rot; }
	void setRotX(float x) { this->rot.x = x; }
	void setRotY(float y) { this->rot.y = y; }
	void setRotZ(float z) { this->rot.z = z; }
	void setScale(float scale) { this->scale = scale; }
	void increasePosition(vec3 dPos) { this->pos += dPos; }
	void increaseRotation(float rx, float ry, float rz);
	void increaseRotation(vec3 dRot) { this->rot += dRot; }
	void setTextureIndex(int texIndex) { this->textureIndex = texIndex; }
	void setDestroyed() { this->destroyed = true; }
	
private:
	void initEntity(TexturedModel* model, vec3 pos, vec3 rot, float scale);
protected:
	TexturedModel* model;
	vec3 pos;
	vec3 rot;
	float scale;
	bool destroyed = false;
	float timeDestroyed = 0.0f;

	//The index of the texture used in a texture atlast
	//(if no texture atlas, just use 0)
	int textureIndex = 0;
};

#endif