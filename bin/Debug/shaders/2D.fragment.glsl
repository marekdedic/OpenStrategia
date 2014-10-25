#version 330 core

in vec2 fUV;

uniform sampler2D oSampler;

void main()
{
	gl_FragColor = texture(oSampler, fUV);
}
