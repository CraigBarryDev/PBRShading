#include "main.h"

//The loader used for loading in models/textures
extern Loader* loader;
EntityRenderer renderer;

//Shaders
StaticShader staticShader;
ParticleShader particleShader;

//Textures
ModelTexture* ballTexture;
ModelTexture* blueTexture;
ModelTexture* greenTexture;
ModelTexture* orangeTexture;
ModelTexture* woodTexture;
ModelTexture* cannonTexture;
ModelTexture* particleTexture;

//Models
RawModel* ballModel;
TexturedModel* ballTexModel;

//Entity Lists
vector<Entity*> ballEntities;
unordered_map<GLuint, vector<Entity*>*> entities;

//Compiles shaders
void initShaders() {
	staticShader = StaticShader("framework/shaders/StaticShader.vert", "framework/shaders/StaticShader.frag");
}

//Cleans up shader resources
void cleanUpShaders() {
	staticShader.cleanUp();
}

//Loads textures
void initTextures() {
	blueTexture = new ModelTexture(loader->loadTexture("textures/blue.jpg"));
	blueTexture->setIsAnimated(true);

	ballTexture = new ModelTexture(loader->loadTexture("textures/metal.jpg"));
	ballTexture->setShineDamper(10.0f);
    ballTexture->setReflectivity(0.8f);

	cannonTexture = new ModelTexture(loader->loadTexture("textures/cannon.jpg"));

	greenTexture = new ModelTexture(loader->loadTexture("textures/green.jpg"));
	greenTexture->setIsAnimated(true);

	orangeTexture = new ModelTexture(loader->loadTexture("textures/orange.jpg"));
	orangeTexture->setIsAnimated(true);

	particleTexture = new ModelTexture(loader->loadTexture("textures/red_particle.png", true));
	particleTexture->setHasTransparency(true);

	woodTexture = new ModelTexture(loader->loadTexture("textures/wood.png"));
	woodTexture->setShineDamper(25.0f);
    woodTexture->setReflectivity(0.2f);
}

//Unloads textures
void cleanUpTextures() {
	delete ballTexture;
	delete blueTexture;
	delete cannonTexture;
	delete greenTexture;
	delete orangeTexture;
	delete woodTexture;
}

//Generates/Loads any required models
void initModels() {
	//Initialize the ball model
	Sphere sphereMesh = Sphere(20, 20, BALL_SIZE);
	ballModel = loader->loadToVAO(sphereMesh.vertices, sphereMesh.normals, sphereMesh.texCoords, sphereMesh.indices);
	ballTexModel = new TexturedModel(ballModel, ballTexture);
}

//Cleans up model resources
void cleanUpModels() {
	delete ballModel;
	delete ballTexModel;
}

void initRenderer() {
	//Initialize the entitiy renderer
    renderer = EntityRenderer(&staticShader, projMatrix);

    //Initialize balls
    int vaoID = ballTexModel->getRawModel()->getVAOID();
    std::pair<GLuint, vector<Entity*>*> ballPair(vaoID, &ballEntities);
    entities.insert(ballPair);
}