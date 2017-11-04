#pragma once

#include "RawModel.h"
#include "ModelTexture.h"
#include "../loader.h"

class TexturedModel {
public:
	TexturedModel(RawModel* model, ModelTexture* texture);

	RawModel* getRawModel() { return rawModel; }
	ModelTexture* getTexture() { return texture; }
private:
	RawModel* rawModel;
	ModelTexture* texture;
};