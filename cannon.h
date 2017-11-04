#ifndef CANNON_H
#define CANNON_H

#include "framework/model/Entity.h"
#include "framework/shaders/StaticShader.h"
#include "cylinder.h"

class Cannon {
public:
	Cannon();
	Cannon(Loader* loader, ModelTexture* tex);
	~Cannon();
	void cleanUp();
	Entity* getEntity() {return ent;}
private:
	RawModel* model;
	ModelTexture* tex;
	TexturedModel* texModel;
	Entity* ent;
};

#endif