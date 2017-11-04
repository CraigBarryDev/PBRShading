#version 330 core

in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;
in float visibility;

in vec3 toCameraVector;

out vec4 outColor;

uniform sampler2D textureSampler;
uniform vec3 lightColor;
uniform float shineDamper;
uniform float reflection;
uniform vec3 skyColor;
uniform vec3 ambient;
uniform float timeDestroyed;

void main() {
	//Normalizing Normals
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);
	
	//Calculating diffuse light
	float diffDotProd = dot(unitNormal, unitLightVector);
	diffDotProd = max(diffDotProd, 0.2f);
	vec3 diffuse = diffDotProd * lightColor;

	//Calculating specular light
	vec3 unitVectorToCamera = normalize(toCameraVector);
	vec3 lightDirection = -unitLightVector;
	vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
	float specDotProd = dot(unitVectorToCamera, reflectedLightDirection);
	specDotProd = max(specDotProd, 0.0f);
	float dampedSpecBrightness = pow(specDotProd, shineDamper);
	vec3 specular = dampedSpecBrightness * reflection * lightColor;

	//Get the texture's color
	vec4 textureColor = texture(textureSampler, pass_textureCoords);

	//Final light
	outColor =  (vec4(ambient, 1.0f) + vec4(diffuse,1.0f)) * textureColor + vec4(specular, 1.0f);

	outColor = mix(outColor, vec4(1.0f, 0.0f, 0.0f, 1.0f), timeDestroyed);
}