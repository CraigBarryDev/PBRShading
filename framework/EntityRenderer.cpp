#include "EntityRenderer.h"

EntityRenderer::EntityRenderer(StaticShader* shader, mat4 projectionMatrix)
{
	this->staticShader = shader;
	shader->start();
	shader->setProjectionMatrix(projectionMatrix);
	shader->stop();
}

void EntityRenderer::render(unordered_map<GLuint, vector<Entity*>*> entitiesMap) {
	if(!entitiesMap.empty()) {
		//Iterate through each of the maps key/value pairs
		for (auto mapEntry = entitiesMap.begin(); mapEntry != entitiesMap.end(); ++mapEntry) {
			//If there are no entities, skip to next entitiy list
			if(mapEntry->second[0].empty())
				continue;

			//Get the textured model from the entity
			TexturedModel* texModel = mapEntry->second[0][0]->getModel();
			prepareTexturedModel(texModel);


			const unsigned nEntities = mapEntry->second[0].size();
			//Iterate through the entities in this entity list		
			for (unsigned int i = 0; i < nEntities; i++) {
				//Get the entity
				Entity* entity = mapEntry->second[0][i];	

				entity->update();
				
				//Prepare each entity for drawing (binding transfromations etc)
				prepareInstance(entity);

				//If the model has indices
				if(texModel->getRawModel()->hasIndices()) {
					//Draw the model with an index buffer
					glDrawElements(GL_TRIANGLES, texModel->getRawModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
				}else {
					//Draw the model without an index buffer
					glDrawArrays(GL_TRIANGLES, 0, texModel->getRawModel()->getVertexCount() / 3);
				}
				
			}

			//Unbind the textured model
			unbindTexturedModel();
		}
	}
	
}

void EntityRenderer::prepareTexturedModel(TexturedModel* model) {
	ModelTexture* modelTex = model->getTexture();
	RawModel* rModel = model->getRawModel();
	
	//Bind the VAO to the context
	glBindVertexArray(rModel->getVAOID());

	//Enable the attribute list index 0 on the VAO (our positional data)
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//Set the shine variables
	staticShader->setShineVariables(modelTex->getShineDamper(), modelTex->getReflectivity());
	staticShader->setUseFakeLighting(modelTex->getUseFakeLighting());

	//Set the texture atlas size
	staticShader->setTextureAtlasSize(vec2(modelTex->getTextureAtlasSizeX(), modelTex->getTextureAtlasSizeY()));

	//Set whether the texture is animated
	staticShader->setUseAnimatedTextures(modelTex->getIsAnimated());

	//Bind the texture to the texture unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, modelTex->getTextureID());

	if (model->getTexture()->getHasTransparency())
		disableCulling();
	else
		enableCulling();

	disableCulling();

}

void EntityRenderer::prepareInstance(Entity* entity) {
	//Creates the transformation matrix from entities position
	mat4 transMatrix = entity->getTransformationMatrix();
	//Sets the transformation matrix in the shader
	staticShader->setTransformationMatrix(transMatrix);

	staticShader->setTextureAtlasOffsets(entity->getTextureOffset());
	staticShader->setTimeDestroyed(entity->getTimeDestroyed());

	//Bind the texture to the texture unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, entity->getModel()->getTexture()->getTextureID());
}

void EntityRenderer::unbindTexturedModel() {
	//Disable the attribute lists from the VAO
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	
	//Unbind the VAO from the context
	glBindVertexArray(0);
}

void EntityRenderer::enableCulling() {
	//Stops back faces from being rendered
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void EntityRenderer::disableCulling() {
	//Disabled back faces from not being rendered
	glDisable(GL_CULL_FACE);
}

