#version 400 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vNormal;
out vec4 vColor;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vPosition;
    vColor = vPosition;
}
