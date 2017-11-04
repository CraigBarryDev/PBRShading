#ifndef PEG_H
#define PEG_H

#include "nSidedPolygon.h"
#include "framework/model/Entity.h"
#include "framework/frameTimer.h"

class Peg {
public:
	Peg();
	Peg(Entity* ent);
	~Peg();

	void update();

	void setAngularVeloc(vec3 vel) { this->angularVelocity = vel; };

	Entity* getEntity() { return entity; }
	const vec3 getAngularVeloc() { return angularVelocity; }
private:
	vec3 angularVelocity = vec3(0.0f);
	vec3 velocity = vec3(0.0f);
	Entity* entity;
	int nSides = 0;
};

#endif