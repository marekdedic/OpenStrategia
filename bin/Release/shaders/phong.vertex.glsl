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
}
