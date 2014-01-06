#version 400 core

in vec4 vColor;
out vec4 fColor;

void main()
{
    // Output color = color specified in the vertex shader,
// interpolated between all 3 surrounding vertices
    fColor = vColor;
}
