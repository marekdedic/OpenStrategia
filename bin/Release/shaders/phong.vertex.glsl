#version 400 core

layout(location = 0) in vec3 vPosition_m;

out vec4 vColor;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(vPosition_m, 1);
    vColor = vec4(vPosition_m, 1);
}
