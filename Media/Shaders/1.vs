#version 330 core

uniform float offsetX;

in vec2 vPos;
in vec3 vColor;
in vec2 vTex;

out vec2 fTex;
out vec3 fColor;

void main()
{
	gl_Position = vec4(vPos.x + offsetX, vPos.y, 0.0f, 1.0f);
	fColor = vColor / 255.0f;
	fTex = vTex;
}