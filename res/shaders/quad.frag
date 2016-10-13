#version 430

in vec2 vUV;

layout(location = 0) uniform sampler2D colorMap;
layout(location = 2) uniform sampler2D backgroundMap;
layout(location = 3) uniform sampler2D depthMap;

out vec4 outColor;

void main()
{
	outColor = texture(colorMap, vUV);

	outColor += (1-outColor.a)*texture(backgroundMap,vUV);
}
