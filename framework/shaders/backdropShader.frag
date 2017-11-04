#version 330 core

in vec2 frag_texCoords;
in vec3 frag_normal;
in vec3 toLightVector;
in vec3 toCameraVector;

out vec4 outColor;

uniform sampler2D tex;
uniform vec3 lightColor;
uniform float shineDamper;
uniform float reflection;
uniform vec3 ambient;

void main() {
	//Normalizing Normals
	vec3 unitNormal = normalize(frag_normal);
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
	// specular = clamp(specular, 0.0f, 1.0f);

	//Get the texture's color
	vec4 textureColor = texture(tex, frag_texCoords);

	//Final light
	outColor =  (vec4(ambient, 1.0f) + vec4(diffuse,1.0f)) * textureColor + vec4(specular, 1.0f);
}