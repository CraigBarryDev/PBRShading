#version 330 core

#define MAX_LIGHTS = 20

out vec4 FragColor;
in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;

uniform vec3 camPos;
uniform vec3 lightPositions[MAX_LIGHTS];
uniform vec3 lightColors[MAX_LIGHTS];
uniform float nLights;

uniform vec3 albedo;
uniform float metallic;
uniform float roughness;
uniform float ao;

const float PI = 3.14159265359;

vec3 fresnelSchlick(float cosTheta, vec3 F0) {
	return F0 + (1.0f - F0) * pow(1.0f - cosTheta, 5.0f);
}

float distributionGGX(vec3 N, vec3 H, float roughness) {
	float a = roughness * roughness;
	float a2 = a*a'
	float NdotH = max(dot(N,H), 0.0f);
	float NDotH2 = NdotH * NdotH;

	float nom = a2;
	float denom = (NDotH2 * (a2 - 1.0f) + 1.0f);
	denom = PI * denom * denom;

	return nom / denom;
}

float geometrySchlickGGX(float NdotV, float roughness) {
	float r = roughness + 1.0f;
	float k = r * r / 8.0f;

	float nom = NdotV;
	float denom = NdotV * (1.0f - k) + k;

	return nom / denom;
}

float geometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
	float NdotV = max(dot(N,V), 0.0f);
	float NdotH = max(dot(N,H), 0.0f);
	float ggx1 = geometrySchlickGGX(NdotL, roughness);
	float ggx2 = geometrySchlickGGX(NdotV, roughness);

	return ggx1 * ggx2;
}

void main() {
	//Get the positions surface normal
	vec3 N = normalize(Normal);
	//Get the viewing vector (from the position to the camera)
	vec3 V = normalize(camPos - WorldPos);

	//The output radiance
	vec3 Lo = vec3(0.0f);

	//Iterate through each of the light sources
	for(int i = 0; i < nLights; i++) {
		//Calculate the light vector
		vec3 L = normalize(lightPositions[i] - WorldPos);
		//Calculate the halfway vector for specular components
		vec3 H = normalize(V + L);

		//Distance between the position of the light source
		float distance = length(lightPositions[i] - WorldPos);
		//Calculate attenuation based on distance from the light source
		float attenuation = 1.0f / (distance * distance);
		//Calculate radiance based on the color multiplied by the attenuation
		vec3 radiance = lightColors[i] * attenuation;

		//The fresenl factor determines the surface reflection at 0 incidence
		vec3 F0 = vec3(0.04f);
		//The fresnel factor is skewed by the metallicness of the object
		F0 = mix(F0, albedo, metallic);
		//The fresnel function demonstrates the phenomenom that reflectivity is 100% at a 90 degree
		//angle to the surface of specular light, (i.e. surfaces look "backlit")
		vec3 F = fresnelSchlick(max(dot(H,V), 0.0f), F0);

		//Distribution function determines the shininess and area of specular reflections
		float NDF = distributionGGX(N, H, roughness);
		//Geometric function accounts for when incoming lights are obstructed and shadowing
		//If a surface is more rough then there is more geometric obstruction/shadowing
		float G = geometrySmith(N, V, L, roughness);

		//Determines the distribution, geometric and distribution functions
		vec3 nominator = NDF * G * F;
		//Normalizes the nominator functions (the + 0.001f is to stop the denominator becoming 0)
		float denominator = 4 * max(dot(N,V), 0.0f) * max(dot(N,L), 0.0f) + 0.001f;
		//Calculates the final specular component
		vec3 specular = nominator / denominator;

		//The fresnel function directly correlates to the specular component of light
		vec3 kS = F;
		//The sum of the diffuse and specular components will be 1 (when not accounting for metallicness),
		//Therefore we can calculate the diffuse component using the specular component
		vec3 kD = vec3(1.0f) - kS;
		//Adjust diffuse based on how metallic an object is
		kD *= 1.0f - metallic;

		//Calculate light intensity based on whether the light actually hits
		//the surface using the dot product of the surface normal and incoming light
		float NdotL = max(dot(N,L), 0.0f);
		//The integration step of the render equation
		Lo += (kD * albedo / PI + specular) * radiance * NdotL;
	}	

	//Calculate ambient lighting
	vec3 ambient = vec3(0.03) * albedo * ao;
	//Calculate final linear scale color
	vec3 color = ambient + Lo;

	//Perform gamma correction and HDR
	color = color / (color + vec3(1.0f));
	color = pow(color, vec3(1.0f / 2.2f));

	//Final output color
	FragColor = vec4(color, 1.0f);
}