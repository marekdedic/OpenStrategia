#version 400 core

layout(location = 0) in vec4 vPosition_m;
layout(location = 1) in vec4 vNormal_m;

out vec4 vNormal_w;
out vec4 toCamera;
out vec4 toLight;

uniform mat4 MVP;
uniform mat4 modelMatrix;
uniform vec4 cPosition_w;
uniform vec4 lPosition_w;

void main()
{
    vec4 vPosition_w = modelMatrix * vPosition_m;
    vNormal_w = modelMatrix * vNormal_m;
    toCamera = cPosition_w - vPosition_w;
    toLight = lPosition_w - vPosition_w;

    gl_Position = MVP * vPosition_m;
}
