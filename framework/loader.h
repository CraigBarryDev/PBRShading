#ifndef LOADER_H
#define LOADER_H

#include "GLHeaders.h"
#include "model/RawModel.h"
#include <vector>

class Loader {
public:
	Loader();
	~Loader();
public:
	void cleanUp();
	RawModel* loadToVAO(vector<GLfloat> positions, vector<GLfloat> normals, vector<GLfloat> texCoords, vector<GLuint> indices);
	RawModel* loadToVAO(vector<GLfloat> positions, vector<GLfloat> normals, vector<GLfloat> texCoords);
	RawModel* loadToVAO(vector<GLfloat> positions, vector<GLfloat> normals, vector<GLuint> indices);
	RawModel* loadToVAO(vector<GLfloat> positions, vector<GLfloat> texCoords);
	RawModel* loadToVAO(GLuint vao, vector<GLfloat> positions, vector<GLfloat> normals);
	RawModel* loadOBJModel(std::string filename);
	GLuint loadTexture(std::string filename, bool hasAlphaChannel = false);
private:
	GLuint createVAO();
	void storeDataInAttributeList(GLuint attributeNumber, GLuint coordinateSize, std::vector<GLfloat> data);
	void unbindVAO();
	void bindIndicesBuffer(std::vector<GLuint> indices);
private:
	std::vector<GLuint> textures = std::vector<GLuint>();
	std::vector<GLuint> vaos = std::vector<GLuint>();
	std::vector<GLuint> vbos = std::vector<GLuint>();
};

#endif