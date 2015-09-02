#version 330 core

layout(location = 0) in vec4 vPosition_m;
layout(location = 1) in vec2 vUV;
layout(location = 2) in vec4 vNormal_m;

out vec4 vNormal_w;
out vec4 vToCamera_w;
out vec4 vToLight_w;
out vec3 fUV;

uniform mat4 MVP;
uniform mat4 modelMatrix;
uniform mat3 uvMatrix;
uniform vec4 cPosition_w;
uniform vec4 lPosition_w;

void main()
{
    vec3 tUV = vec3(vUV.x, vUV.y, 1);
    fUV = uvMatrix * tUV;
    vec4 vPosition_w = modelMatrix * vPosition_m;
    vNormal_w = normalize(modelMatrix * vNormal_m);
    vToCamera_w = normalize(cPosition_w - vPosition_w);
    vToLight_w = normalize(lPosition_w - vPosition_w);
    gl_Position = MVP * vPosition_m;
}
