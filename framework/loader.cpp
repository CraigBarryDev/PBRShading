#include "loader.h"

Loader::Loader() {}

Loader::~Loader() {}

RawModel* Loader::loadToVAO(vector<GLfloat> positions, vector<GLfloat> normals, vector<GLfloat> texCoords, vector<GLuint> indices) {
	//Creates the VAO object and stores its ID in vaoID
	GLuint vaoID = createVAO();
	//Store the positional data in the first index of the attribute list of the VAO
	storeDataInAttributeList(0, 3, positions);
	storeDataInAttributeList(1, 2, texCoords);
	storeDataInAttributeList(2, 3, normals);
	//Bind indices buffer to VAO
	bindIndicesBuffer(indices);
	//Unbind the VAO from the context
	unbindVAO();
	//Return the model
	return new RawModel(vaoID, indices.size(), 1.0f);
}

RawModel* Loader::loadToVAO(vector<GLfloat> positions, vector<GLfloat> normals, vector<GLfloat> texCoords) {
	//Creates the VAO object and stores its ID in vaoID
	GLuint vaoID = createVAO();
	//Store the positional data in the first index of the attribute list of the VAO
	storeDataInAttributeList(0, 3, positions);
	storeDataInAttributeList(1, 2, texCoords);
	storeDataInAttributeList(2, 3, normals);
	//Unbind the VAO from the context
	unbindVAO();
	//Return the model
	return new RawModel(vaoID, positions.size(), 1.0f, false);
}

RawModel* Loader::loadToVAO(vector<GLfloat> positions, vector<GLfloat> normals, vector<GLuint> indices) {
	//Creates the VAO object and stores its ID in vaoID
	GLuint vaoID = createVAO();
	//Store the positional data in the first index of the attribute list of the VAO
	storeDataInAttributeList(0, 3, positions);
	storeDataInAttributeList(1, 3, normals);
	//Bind indices buffer to VAO
	bindIndicesBuffer(indices);
	//Unbind the VAO from the context
	unbindVAO();
	//Return the model
	return new RawModel(vaoID, indices.size(), 1.0f);
}

RawModel* Loader::loadToVAO(vector<GLfloat> positions, vector<GLfloat> texCoords) {
	//Creates the VAO object and stores its ID in vaoID
	GLuint vaoID = createVAO();
	//Store the positional data in the first index of the attribute list of the VAO
	storeDataInAttributeList(0, 3, positions);
	storeDataInAttributeList(1, 2, texCoords);
	//Unbind the VAO from the context
	unbindVAO();
	//Return the model
	return new RawModel(vaoID, positions.size(), 1.0f, false);
}

RawModel* Loader::loadToVAO(GLuint vao, vector<GLfloat> positions, vector<GLfloat> normals) {
	//Bind the VAO
	glBindVertexArray(vao);
	//Store the vertex data in corresponding attribute lists
	storeDataInAttributeList(0, 3, positions);
	storeDataInAttributeList(1, 3, normals);
	//Unbind the vao
	unbindVAO();
	//Return the model
	return new RawModel(vao, positions.size(), 1.0f, false);
}

GLuint Loader::createVAO() {
	//Creates the vao and stores its ID in the vaoID variable
	GLuint vaoID;
	//Generates the VAO
	glGenVertexArrays(1, &vaoID);
	//Adds the VAO to the list of vaos
	// vaos.push_back(vaoID);
	//Binds the VAO to the context
	glBindVertexArray(vaoID);
	//Returns the vaoID
	return vaoID;
}

void Loader::storeDataInAttributeList(GLuint attributeNumber, GLuint coordinateSize,  std::vector<GLfloat> data) {
	//Creates the VBO and stores its ID in the vboID variable
	GLuint vboID;
	glGenBuffers(1, &vboID);

	//Adds the VBO to the list of VBOs
	// vbos.push_back(vboID);

	//Binds the vbo to GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	//Stores the data into the VBO
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);

	//Adds the VBO to the VAO
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	//Enable the vertex attribute to be used (when passed to a shader)
	glEnableVertexAttribArray(attributeNumber);

	//Unbinds the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bindIndicesBuffer(std::vector<GLuint> indices) {
	//Creates the ebo (element array buffer/index buffer)
	GLuint eboID;
	glGenBuffers(1, &eboID);
	//Add it to the list of vbos
	// vbos.push_back(eboID);
	//Bind the array buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	//Bind the element data to the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

GLuint Loader::loadTexture(std::string filename, bool hasAlphaChannel) {
	int width, height;

	//Load the image
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, hasAlphaChannel ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);

	//Stores the ID of the texture
	GLuint texture;

	//Create the texture object and store the unique ID in texture
	glGenTextures(1, &texture);

	//Add the texture ID to the list of textures
	// textures.push_back(texture);

	//Bind the texture to GL_TEXTURE_2D target
	glBindTexture(GL_TEXTURE_2D, texture);

	//Get the format of the image based on if it has an alpha channel or not
	GLuint format = hasAlphaChannel ? GL_RGBA : GL_RGB;

	//Bind the image to the texture object
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);

	//Generate the textures mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	//Set the scaling mode of the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Free the image data as its no longer needed
	SOIL_free_image_data(image);

	//Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

void Loader::unbindVAO() {
	//Unbinds the VAO from the context
	glBindVertexArray(0);
}

void Loader::cleanUp() {
	for (unsigned int i = 0; i < vaos.size(); i++) {
		glDeleteVertexArrays(1, &vaos[i]);
	}
	for (unsigned int i = 0; i < vbos.size(); i++) {
		glDeleteVertexArrays(1, &vbos[i]);
	}
	for (unsigned int i = 0; i < textures.size(); i++) {
		glDeleteTextures(1, &textures[i]);
	}
}