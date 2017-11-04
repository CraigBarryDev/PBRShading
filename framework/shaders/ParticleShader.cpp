#include "ParticleShader.h"

ParticleShader::ParticleShader(string vertexFile, string fragmentFile) 
	:
Shader(vertexFile, fragmentFile)
{
	bindAttributes();
}

void ParticleShader::bindAttributes() {
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
}