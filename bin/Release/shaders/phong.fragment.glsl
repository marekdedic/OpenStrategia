#version 400 core

in vec4 vColor;
in vec3 vPosition_w;
in vec3 vNormal_c;
in vec3 EyeDirection_c;
in vec3 LightDirection_c;

out vec4 fColor;

uniform vec3 LightPosition_w;

void main()
{
	fColor = vColor;
}
