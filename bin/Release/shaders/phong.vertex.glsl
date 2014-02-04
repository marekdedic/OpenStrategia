#version 400 core

layout(location = 0) in vec3 vPosition_m;
layout(location = 1) in vec3 vNormal_m;

out vec4 vColor;

uniform mat4 MVP;
uniform vec3 cPosition_g;
uniform vec3 lPosition_g;

void main()
{
    gl_Position = MVP * vec4(vPosition_m, 1);
    vColor = vec4(vPosition_m, 1);
}
