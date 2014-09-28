#version 330 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vUV;

out vec2 fUV;

uniform mat4 matrix;

void main()
{
    fUV = vUV;
    gl_Position = matrix * vPosition;
}