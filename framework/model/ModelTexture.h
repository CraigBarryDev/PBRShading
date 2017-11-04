#pragma once

#include "../GLHeaders.h"

class ModelTexture {

public:
	ModelTexture(GLuint id);
	const GLuint getTextureID() { return textureID; }

	//Getters
	const float getShineDamper() { return shineDamper; }
	const float getReflectivity() { return reflectivity; }
	const bool getHasTransparency() { return hasTransparency; }
	const bool getUseFakeLighting() { return useFakeLighting; }
	const bool getIsAnimated() { return isAnimated; }
	const int getTextureAtlasSizeX() { return texAtlasNRows; }
	const int getTextureAtlasSizeY() { return texAtlasNCols; }

	//Setters
	void setShineDamper(float shineDamper) { this->shineDamper = shineDamper; }
	void setReflectivity(float reflectivity) { this->reflectivity = reflectivity;  }
	void setHasTransparency(bool hasTransparency) { this->hasTransparency = hasTransparency; }
	void setUseFakeLighting(bool useFakeLighting) { this->useFakeLighting = useFakeLighting; }
	void setIsAnimated(bool isAnimated) { this->isAnimated = isAnimated; }
	void setTextureAtlasSize(int sizeX, int sizeY) { texAtlasNRows = sizeX;	texAtlasNCols = sizeY; }
private:
	int texAtlasNRows = 1;
	int texAtlasNCols = 1;
	float shineDamper = 1.0f;
	float reflectivity = 0.0f;
	bool hasTransparency = false;
	bool useFakeLighting = false;
	bool isAnimated = false;
	GLuint textureID;
};