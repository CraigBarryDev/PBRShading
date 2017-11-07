#include "PBRShader.h"

PBRShader::PBRShader(string vertexFile, string fragmentFile)
	:
Shader(vertexFile, fragmentFile) {
	bindAttributes();
}

void PBRShader::bindAttributes() {
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
	bindAttribute(2, "normal");
}

void setAlbedo(vec3 albedo) {
	setUniform("albedo", albedo);
}

void setMetallic(float metallic) {
	setUniform("metallic", metallic);
}

void setRoughness(float roughness) {
	setUniform("roughness", roughness);
}

void setAmbientOcclusion(float ao) {
	setUniform("ao", ao);
}

void setCamPos(vec3 camPos) {
	setUniform("camPos", camPos);
}

void setNLights(float nLights) {
	setUniform("nLights", nLights);
}

void setLightPos(int lightIndex, vec3 lightPos) {
	setUniform(string("lightPositions[") + string(lightIndex) + string("]"), lightPos);
}

void setLightColor(int lightIndex, vec3 lightColor) {
	setUniform(string("lightColors[") + string(lightIndex) + string("]"), lightColor);
}