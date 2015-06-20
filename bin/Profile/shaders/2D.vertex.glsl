#version 330 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 vUV;

out vec3 fUV;

uniform mat4 matrix;
uniform mat3 uvMatrix;

void main()
{
    fUV = uvMatrix * vUV;
    gl_Position = matrix * vPosition;
}
