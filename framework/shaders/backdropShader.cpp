#include "backdropShader.h"

BackdropShader::BackdropShader(string vertexFile, string fragmentFile)
	:
Shader(vertexFile, fragmentFile)
{
	bindAttributes();
}

void BackdropShader::bindAttributes() { 
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
	bindAttribute(2, "normal");
}

void BackdropShader::setLightPosition(vec3 lightPos) {
	setUniform("lightPosition", lightPos);
}

void BackdropShader::setAmbientLight(vec3 ambient) {
	setUniform("ambient", ambient);
}

void BackdropShader::setLightColor(vec3 lightColor) {
	setUniform("lightColor", lightColor);
}

void BackdropShader::setShineVariables(float damper, float reflection) {
	setUniform("shineDamper", damper);
	setUniform("reflection", reflection);
}