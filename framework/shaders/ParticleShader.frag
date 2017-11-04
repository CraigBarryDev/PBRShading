#version 330 core

in vec2 pass_textureCoords;

out vec4 outColor;

uniform sampler2D textureSampler;
uniform float runningTime;

void main() {
	//Get the texture's color
	vec4 textureColor = texture(textureSampler, pass_textureCoords);

	//If the fragment is transparent, discard it
	if(textureColor.a < 0.5f) {
		discard;
	}

	//Final color
	outColor =  vec4(textureColor.xyz, 1.0f - runningTime);
}