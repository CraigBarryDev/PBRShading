#ifndef SHADERS_H
#define SHADERS_H

#include "GLHeaders.h"

#include <string>

class Shader {
public: 
	Shader();
	Shader(string vertexFile, string fragmentFile);
	~Shader();
	void cleanUp();
	void start();
	void stop();
protected:
	virtual void bindAttributes() = 0;
	void bindAttribute(GLuint attribute, string variableName);
	inline GLuint getUniformLoc(const GLchar* uniformName) { return glGetUniformLocation(programID, uniformName); }
	void setUniform(const GLchar* uniformName, const int val);
	void setUniform(const GLchar* uniformName, const double val);
	void setUniform(const GLchar* uniformName, const float val);
	void setUniform(const GLchar* uniformName, const glm::mat4& mat);
	void setUniform(const GLchar* uniformName, const glm::vec4& vec);
	void setUniform(const GLchar* uniformName, const glm::vec3& vec);
	void setUniform(const GLchar* uniformName, const glm::vec2& vec);
private:
	GLuint loadShader(std::string file, GLenum type);
private:
	GLuint programID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;
};

#endif