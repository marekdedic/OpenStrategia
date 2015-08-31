#version 330 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vUV;

out vec3 fUV;

uniform mat4 matrix;
uniform mat3 uvMatrix;

void main()
{
    vec3 tUV = vec3(vUV.x, vUV.y, 1);
    fUV = uvMatrix * tUV;
    gl_Position = matrix * vPosition;
}
