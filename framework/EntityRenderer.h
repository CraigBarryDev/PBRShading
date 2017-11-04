#include "shaders/StaticShader.h"
#include "model/Entity.h"
#include <unordered_map>

#ifndef ENTITY_RENDERER_H
#define ENTITY_RENDERER_H

class EntityRenderer {
public:
	EntityRenderer() {}
	EntityRenderer(StaticShader* shader, mat4 projectionMatrix);
	void render(unordered_map<GLuint, vector<Entity*>*>);

private:
	void prepareTexturedModel(TexturedModel* model);
	void unbindTexturedModel();
	void prepareInstance(Entity* entity);
	void enableCulling();
	void disableCulling();

private:
	StaticShader* staticShader;
};

#endif