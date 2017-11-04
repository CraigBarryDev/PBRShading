#ifndef PARTICLES_H
#define PARTICLES_H

#include "framework/loader.h"
#include "framework/frameTimer.h"
#include "framework/maths.h"
#include "framework/GLHeaders.h"
#include "framework/model/Entity.h"
#include "framework/shaders/ParticleShader.h"

#define MAX_PARTICLE_SPEED 4.0f
#define MIN_PARTICLE_SPEED 1.0f

#define MAX_PARTICLE_SIZE 2.0f
#define MIN_PARTICLE_SIZE 1.0f

#define MAX_RUNNING_TIME 1.0f

class Particle {
public:
	Particle() {}
public:
	vec3 pos;
	vec3 veloc;
	float scale;
};

class Particles {
public:
	Particles();
	Particles(Loader* loader, int nParticles, ModelTexture* particleTexture, ParticleShader shader, vec3 srcPos);
	~Particles();
	void render();
	void cleanUp();
	const bool finished() { return runningTime > MAX_RUNNING_TIME; }
private:
	GLuint vao;
	vec3 srcPos;
	ParticleShader shader;
	vector<Particle> particles;
	ModelTexture* texture;
	RawModel* pModel;
	float runningTime = 0.2f;
};


#endif
