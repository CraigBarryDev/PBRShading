#include "../shaders.h"

#ifndef PARTICLE_SHADER_H
#define PARTICLE_SHADER_H

class ParticleShader : public Shader {
public:
	ParticleShader() {}
	ParticleShader(string vertexFile, string fragmentFile);

	void setRunningTime(float time) { setUniform("runningTime", time); }
	void setParticlePos(vec3 pos) { setUniform("partPosition", pos); }
	void setParticleVeloc(vec3 veloc) { setUniform("velocity", veloc); }
	void setViewMatrix(glm::mat4 mat) { setUniform("viewMatrix", mat); }
	void setProjectionMatrix(mat4 mat) { setUniform("projectionMatrix", mat); }

protected:
	virtual void bindAttributes() override;
};

#endif