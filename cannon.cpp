#include "cannon.h"

Cannon::Cannon() {}

Cannon::Cannon(Loader* loader, ModelTexture* tex) {
	this->tex = tex;
	//Generates a cylinder mesh
	Cylinder cylinderMesh = Cylinder(20, 20, 1.0f);
	//Generates a model from the cylinder mesh
	model = loader->loadToVAO(cylinderMesh.vertices, cylinderMesh.normals, cylinderMesh.texCoords, cylinderMesh.indices);
	//Generates textured model
	texModel = new TexturedModel(model, tex);
	//Generates entity
	ent = new Entity(texModel);
}

Cannon::~Cannon() {}

void Cannon::cleanUp() {
	delete model;
	delete texModel;
	delete ent;
}