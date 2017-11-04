#include "../shaders.h"

#ifndef BACKDROP_SHADERS_H
#define BACKDROP_SHADERS_H

class BackdropShader : public Shader {
public:
	BackdropShader() {}
	BackdropShader(string vertexFile, string fragmentFile);
	void setLightPosition(vec3 lightPos);
	void setAmbientLight(vec3 ambient);
	void setLightColor(vec3 lightColor);
	void setShineVariables(float damper, float reflection);
protected:
	virtual void bindAttributes() override;
};

#endif