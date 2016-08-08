#version 330 core

in vec2 vPos;
in vec2 vTex;
in vec4 vColor;

out vec2 fTex;
out vec4 fColor;

void main()
{
	gl_Position = vec4(vPos, 0.0f, 1.0f);
	fColor = vColor / 255.0f;
	fTex = vTex;
}