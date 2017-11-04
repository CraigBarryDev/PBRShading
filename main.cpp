#include "main.h"

#include <vector>
#include <unordered_map>
#include "framework/loader.h"
#include "framework/GLHeaders.h"

//Main initialization
void init(void) {
	//Creates the loading object
	loader = new Loader();

	//Initialize game resources
    initTextures();
    initShaders();
    initModels();
    initRenderer();

    const int N_BALLS = 10;
    const float START_X = -15.0f;
    const float START_Y = 15.0f;
    const float START_Z = -50.0f;

    float x = START_X;
    float y = START_Y;
    float z = START_Z;

    for(int i = 0; i < 10; i++) {
        

        for(int j = 0; j < 10; j++) {
            Entity* ballEntity = new Entity(ballTexModel);
            ballEntity->setPosition(vec3(x,y,z));
            ballEntities.push_back(ballEntity);
            
            y -= START_Y / ((N_BALLS - 1) / 2.0f);
        }

        x -= START_X / ((N_BALLS - 1) / 2.0f);
        y = START_Y;
    }
}

//Update function called before each draw call to update program state
void update(void) {
    handleMouse();
    handleKeyboard();
}


//Called every frame to render objects before the buffers are swapped
void display(void) {
    //Calculate the view/projection matrices
    mat4 projMatrix = Maths::createProjectionMatrix(windowWidth, windowHeight, projFOV, projZNear, projZFar);
    mat4 viewMatrix = Maths::createViewMatrix(0.0f, 0.0f, vec3(0.0f, -0.0f, 0.0f));

    staticShader.start();
    staticShader.setProjectionMatrix(projMatrix);
    staticShader.setViewMatrix(viewMatrix);
    staticShader.setLightColor(LIGHT_COLOR);
    staticShader.setLightPosition(LIGHT_POS);
    staticShader.setAmbientLight(0.7f * LIGHT_AMBIENT);
    staticShader.setTime(getTimeSec());
    //Render all entities
	renderer.render(entities);
}

//Called when the application ends to deallocate memory
void cleanUp(void) {
	//Destroys the loading object
	loader->cleanUp();
	delete loader;

	//Cleans up game resources
	cleanUpModels();
	cleanUpShaders();
	cleanUpTextures();
}
