#version 330 core

in vec3 position;
in vec2 textureCoords;

out vec2 pass_textureCoords;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform float runningTime;
uniform vec3 partPosition;
uniform vec3 velocity;

void main() {
	//world space
	vec4 worldPosition = vec4((runningTime * velocity) + (partPosition + position), 1.0f);
	//camera space
	vec4 posRelativeToCamera = viewMatrix * worldPosition;
	//view space
	gl_Position = projectionMatrix * posRelativeToCamera;

	//Set texture coordinates
	pass_textureCoords = textureCoords;
}
