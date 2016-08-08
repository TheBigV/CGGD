#version 330 core

uniform sampler2D textureColor;

in vec4 fColor;
in vec2 fTex;

out vec4 outColor;

void main()
{
	outColor = fColor * texture(textureColor, fTex);
}