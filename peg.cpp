#include "peg.h"

Peg::Peg() {}

Peg::~Peg() {}

Peg::Peg(Entity* ent)
	:
entity(ent)
{}

void Peg::update() {
	entity->increaseRotation(angularVelocity * getFrameTime());
	entity->increasePosition(velocity * getFrameTime());
}