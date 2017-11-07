#include "../shaders.h"

#ifndef PBR_SHADERS_H
#define PBR_SHADERS_H

class PBRShader : public Shader {
public:
	PBRShader() {}
	PBRShader(string vertexFile, string fragmentFile);

	void setAlbedo(vec3 albedo);
	void setMetallic(float metallic);
	void setRoughness(float roughness);
	void setAmbientOcclusion(float ao);

	void setCamPos(vec3 camPos);
	void setLightPos(int lightIndex, vec3 lightPos);
	void setLightColor(int lightIndex, vec3 lightColor);
protected:
	virtual void bindAttributes() override;
};

#endif