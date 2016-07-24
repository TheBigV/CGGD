#version 330 core

uniform sampler2D textureColor;

in vec3 fColor;
in vec2 fTex;

out vec4 outColor;

void main()
{
	outColor = vec4(fColor, 1.0f) * texture(textureColor, fTex);
}