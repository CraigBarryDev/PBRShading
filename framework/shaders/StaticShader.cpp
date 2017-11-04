#include "StaticShader.h"

StaticShader::StaticShader(string vertexFile, string fragmentFile) 
	:
Shader(vertexFile, fragmentFile)
{
	bindAttributes();
}

void StaticShader::setTransformationMatrix(glm::mat4 mat) {
	setUniform("transformationMatrix", mat); 
}

void StaticShader::setProjectionMatrix(mat4 mat) {
	setUniform("projectionMatrix", mat); 
}

void StaticShader::setViewMatrix(mat4 mat) {
	setUniform("viewMatrix", mat);
}

void StaticShader::setLightPosition(vec3 lightPos) {
	setUniform("lightPosition", lightPos);
}

void StaticShader::setAmbientLight(vec3 ambient) {
	setUniform("ambient", ambient);
}

void StaticShader::setLightColor(vec3 lightColor) {
	setUniform("lightColor", lightColor);
}

void StaticShader::setShineVariables(float damper, float reflection) {
	setUniform("shineDamper", damper);
	setUniform("reflection", reflection);
}

void StaticShader::setUseFakeLighting(bool useFakeLighting) {
	setUniform("useFakeLighting", (int)useFakeLighting);
}

void StaticShader::setSkyColour(vec3 skyColor) {
	setUniform("skyColor", skyColor);
}

void StaticShader::setTextureAtlasOffsets(vec2 offsets) {
	setUniform("texAtlasPos", offsets);
}

void StaticShader::setTextureAtlasSize(vec2 size) {
	setUniform("texAtlasSize", size);
}

void StaticShader::setTime(float time) {
	setUniform("time", time);
}

void StaticShader::setUseAnimatedTextures(bool animateTextures) {
	setUniform("useAnimatedTextures", animateTextures);
}

void StaticShader::setTimeDestroyed(float time) {
	setUniform("timeDestroyed", time);
}

void StaticShader::bindAttributes() {
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
	bindAttribute(2, "normal");
}