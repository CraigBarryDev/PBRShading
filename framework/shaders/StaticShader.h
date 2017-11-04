#include "../shaders.h"

#ifndef STATIC_SHADERS_H
#define STATIC_SHADERS_H

class StaticShader : public Shader {
public:
	StaticShader() {}
	StaticShader(string vertexFile, string fragmentFile);

	void setAmbientLight(vec3 ambient);
	void setTransformationMatrix(glm::mat4 mat);
	void setProjectionMatrix(mat4 mat);
	void setViewMatrix(mat4 mat);
	void setLightPosition(vec3 lightPos);
	void setLightColor(vec3 lightColor);
	void setShineVariables(float damper, float reflection);
	void setUseFakeLighting(bool useFakeLighting);
	void setSkyColour(vec3 skyColor);
	void setTime(float time);
	void setUseAnimatedTextures(bool animateTextures);
	void setTimeDestroyed(float time);

	void setTextureAtlasOffsets(vec2 offsets);
	void setTextureAtlasSize(vec2 size);
protected:
	virtual void bindAttributes() override;
};

#endif