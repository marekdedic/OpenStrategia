#version 400 core

layout(location = 0) in vec4 vPosition_m;
layout(location = 1) in vec4 vNormal_m;

out vec4 vColor;

uniform mat4 MVP;
uniform mat4 modelMatrix;
uniform vec4 cPosition_w;
uniform vec4 lPosition_w;

void main()
{
    float phongExp = 5;
    vec4 lSpecularColor = vec4(0.6, 0.6, 0.6, 1);
    vec4 mDiffuseColor = vec4(0.3, 0.5, 0.5, 1);
    vec4 mSpecularColor = mDiffuseColor;

    vec4 vPosition_w = modelMatrix * vPosition_m;
    vec4 vNormal_w = modelMatrix * vNormal_m;
    vec4 toCamera = cPosition_w - vPosition_w;
    vec4 toLight = lPosition_w - vPosition_w;
    vec4 reflection = 2 * dot(vNormal_w, toLight) * vNormal_w - toLight;
    float cosTheta = clamp(dot(reflection, toCamera), 0, 1);
    vec4 vSpecularColor = pow(cosTheta, phongExp) * mSpecularColor * lSpecularColor;

    gl_Position = MVP * vPosition_m;
    vColor = mDiffuseColor + vSpecularColor;
}
