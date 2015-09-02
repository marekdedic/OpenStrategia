#version 330 core

layout(location = 0) in vec4 vPosition_m;
layout(location = 1) in vec4 vNormal_m;
out vec4 vColor;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vPosition_m;
    vColor = vPosition_m;
}
