#version 400 core

layout(location = 0) in vec3 vPosition_m;
layout(location = 1) in vec3 vNormal_m;

out vec4 vColor;
out vec3 vPosition_w;
out vec3 vNormal_c;
out vec3 EyeDirection_c;
out vec3 LightDirection_c;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 LightPosition_w;

void main()
{
    gl_Position = MVP * vec4(vPosition_m, 1);
    vColor = vec4(vPosition_m, 1);
	vPosition_w = (M * vec4(vPosition_m, 1)).xyz;
	vec3 vPosition_c = (V * M * vec4(vPosition_m, 1)).xyz;
	EyeDirection_c = vec3(0,0,0) - vPosition_c;
	vec3 LightPosition_c = (V * vec4(LightPosition_w, 1)).xyz;
	LightDirection_c = LightPosition_c + EyeDirection_c;
	vNormal_c = (V * M * vec4(vNormal_m, 0)).xyz; // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
}
