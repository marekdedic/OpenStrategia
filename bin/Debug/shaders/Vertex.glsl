#version 400 core

layout(location = 0) in vec4 vPosition;
out vec4 vColor;

uniform mat4 MVP;


void main()
{
    gl_Position = MVP * vPosition;
    vColor = vPosition;
}
