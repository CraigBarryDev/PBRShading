#version 330 core

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

out vec2 pass_textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;
out float visibility;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform vec3 lightPosition;
uniform vec2 texAtlasPos;
uniform vec2 texAtlasSize;
uniform int useFakeLighting;

uniform float time;
uniform int useAnimatedTextures;

const float density = 0.007;
const float gradient = 0.8;

void main() {
	//world space
	vec4 worldPosition = transformationMatrix * vec4(position.xyz, 1.0f);
	//camera space
	vec4 posRelativeToCamera = viewMatrix * worldPosition;
	//view space
	gl_Position = projectionMatrix * posRelativeToCamera;

	if(useAnimatedTextures == 0) {
		pass_textureCoords = textureCoords / texAtlasSize + texAtlasPos;
	}else {
		if(textureCoords.x > 0.0f && textureCoords.y > 0.0f) {
			float x = mod(time, 6.24);
			pass_textureCoords = vec2(0.1f * (sin(textureCoords * x * 0.2f)));
		}else {
			pass_textureCoords = textureCoords;
		}
	}

	vec3 tempNormal = normal;
	if(useFakeLighting == 1) {
		tempNormal = vec3(0.0f, 1.0f, 0.0f);
	}

	surfaceNormal = (transformationMatrix * vec4(tempNormal, 0.0f)).xyz;

	toLightVector = lightPosition - worldPosition.xyz;

	//Getting the inverse will negate the matrix and multiplying it by the vec4 will keep the
	//translation (as that is the 4th column of the matrix, thereby getting the true location
	//of the camera, rather than the negated transformation given by the viewMatrix)
	toCameraVector = (inverse(viewMatrix) * vec4(0.0f,0.0f,0.0f,1.0f)).xyz - worldPosition.xyz;

	//Gets the distance from the camera to the vertex
	float distance = length(posRelativeToCamera.xyz);
	visibility = exp(-pow((distance*density), gradient));
	//Maxes the value at 1.0f and minimizes it at 0.0f
	visibility = clamp(visibility, 0.0f, 1.0f);
}