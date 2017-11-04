#ifndef BACKDROP_H
#define BACKDROP_H

#include "framework/GLHeaders.h"
#include "framework/model/Entity.h"
#include "framework/shaders/backdropShader.h"

class Backdrop {
public:
	Backdrop();
	Backdrop(Loader* loader, ModelTexture* tex, BackdropShader* bShader);
	~Backdrop();
	void cleanUp();
	void render();

private:
	BackdropShader* shader;
	RawModel* model;
	ModelTexture* tex;

	float vertices[12] = {
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
	};

	float normals[12] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
	};

	float texCoords[8] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f, 
		1.0f, 1.0f,
	};

	int indices[6] = {
		0, 3, 1,
		3, 2, 1,
	};
};

#endif