#version 330 core

layout(location = 0) in vec4 vPosition_m;
layout(location = 2) in vec4 vNormal_m;

out vec4 vNormal_w;
out vec4 vToLight_w;
out vec4 vHalfway_w;

uniform mat4 MVP;
uniform mat4 modelMatrix;
uniform vec4 cPosition_w;
uniform vec4 lPosition_w;

void main()
{
    vec4 vPosition_w = modelMatrix * vPosition_m;
    vNormal_w = normalize(modelMatrix * vNormal_m);
    vec4 vToCamera_w = cPosition_w - vPosition_w;
    vToLight_w = normalize(lPosition_w - vPosition_w);
    vHalfway_w = normalize((vToCamera_w + vToLight_w) / length(vToCamera_w + vToLight_w));
    gl_Position = MVP * vPosition_m;
}
