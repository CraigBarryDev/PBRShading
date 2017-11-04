#include "backdrop.h"

Backdrop::Backdrop() {}

Backdrop::Backdrop(Loader* loader, ModelTexture* tex, BackdropShader* bShader) {
	vector<GLfloat> vPositions(std::begin(vertices), std::end(vertices));
	vector<GLfloat> vNormals(std::begin(normals), std::end(normals));
	vector<GLfloat> vTexCoords(std::begin(texCoords), std::end(texCoords));
	vector<GLuint> vIndices(std::begin(indices), std::end(indices));
	model = loader->loadToVAO(vPositions, vNormals, vTexCoords, vIndices);
	this->tex = tex;
	shader = bShader;
}

Backdrop::~Backdrop() {}

void Backdrop::cleanUp() {
	delete model;
}

void Backdrop::render() {
	//Bind the shader program
	shader->start();

	//Disable depth testing when drawing backdrop
	glDisable(GL_DEPTH_TEST);

	//Bind the VAO to the context
	glBindVertexArray(model->getVAOID());

	//Enable the attribute list index 0 on the VAO (our positional data)
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//Bind the texture to the texture unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex->getTextureID());

	//Draw the model
	glDrawElements(GL_TRIANGLES, model->getVertexCount(), GL_UNSIGNED_INT, 0);

	//Disable the attribute lists from the VAO
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	
	//Unbind the VAO from the context
	glBindVertexArray(0);

	//Re-enable depth testing
	glEnable(GL_DEPTH_TEST);

	//Unbind the shader program
	shader->stop();
}