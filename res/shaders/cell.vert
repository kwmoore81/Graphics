#version 430

out vec3 normal;
layout (location = 0) in vec4 position;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 proj;

void main()
{

	normal = gl_NormalMatrix * gl_Normal;
	gl_Position = proj * view * model * position;
	//gl_Position = ftransform();
	
}