#version 430

layout(location = 0) in vec4 position;
layout(location = 3) in vec2 texcoord;

out vec2 vUV;

varying vec3 normal;

void main()
{
	vUV = texcoord;
	gl_Position = position;
}