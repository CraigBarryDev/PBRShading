#include "shaders.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader() {}

Shader::Shader(string vertexFile, string fragmentFile) {
	vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
	fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	GLchar errorLog[512];
	GLint success;
	//Gets the linking status of the shader program
	glGetProgramiv(programID, GL_LINK_STATUS, &success);

	//Check if linking the shaders failed
	if (!success) {
		//Get the error that occured
		glGetProgramInfoLog(programID, 512, NULL, errorLog);
		std::cout << errorLog << std::endl;
	}
}

Shader::~Shader() {}

void Shader::cleanUp() {
	stop();
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteProgram(programID);
}

void Shader::start() {
	glUseProgram(programID);
}

void Shader::stop() {
	glUseProgram(0);
}

GLuint Shader::loadShader(std::string file, GLenum type) {
	std::ifstream f;
	f.open(file);

	if (!f) {
		cout << "Could not open file for shader compilation " << file << endl;
		return 0;
	}

	string shaderCode(static_cast<stringstream const&>(stringstream() << f.rdbuf()).str());

	GLuint shader = glCreateShader(type);
	const GLchar* sCode = shaderCode.c_str();

	glShaderSource(shader, 1, &sCode, NULL);
	glCompileShader(shader);

	GLint success;
	GLchar errorLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, errorLog);
		cout << "ERROR::SHADER::COMPILATION_FAILED\n" << errorLog << std::endl;
	};

	return shader;
}

void Shader::bindAttribute(GLuint attribute, string variableName) {
	glBindAttribLocation(programID, attribute, variableName.c_str());
}

#pragma region Set Shader Uniforms

void Shader::setUniform(const GLchar* uniformName, const int val) {
	GLuint loc = getUniformLoc(uniformName);
	glUniform1i(loc, val);
}

/*void Shader::setUniform(const GLchar* uniformName, const double val) {
	GLuint loc = getUniformLoc(uniformName);
	glUniform1d(loc, val);
}*/

void Shader::setUniform(const GLchar* uniformName, const float val) {
	GLuint loc = getUniformLoc(uniformName);
	glUniform1f(loc, val);
}

void Shader::setUniform(const GLchar* uniformName, const glm::mat4& mat) {
	GLuint loc = getUniformLoc(uniformName);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setUniform(const GLchar* uniformName, const glm::vec4& vec) {
	GLuint loc = getUniformLoc(uniformName);
	glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
}

void Shader::setUniform(const GLchar* uniformName, const glm::vec3& vec) {
	GLuint loc = getUniformLoc(uniformName);
	glUniform3f(loc, vec.x, vec.y, vec.z);
}

void Shader::setUniform(const GLchar* uniformName, const glm::vec2& vec) {
	GLuint loc = getUniformLoc(uniformName);
	glUniform2f(loc, vec.x, vec.y);
}

#pragma endregion
