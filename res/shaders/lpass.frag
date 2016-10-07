#version 430

layout(location = 0) uniform mat4 view;
layout(location = 1) uniform mat4 proj;

layout(location = 2) uniform sampler2D albedoMap;
layout(location = 3) uniform sampler2D normalMap;
layout(location = 4) uniform sampler2D specularMap;
layout(location = 5) uniform sampler2D positionMap;
layout(location = 6) uniform sampler2D depthMap;

layout(location = 0) out vec4 outColor;
layout(location = 1) out vec4 outAlbedo;
layout(location = 2) out vec4 outSpecular;

in vec2 vUV;

varying vec3 normal;

layout(location = 7) uniform vec4 lDir;// = normalize(vec4(1,-1,-1,0));
layout(location = 8) uniform vec4 lCol;// = vec4(1,1,1,1);


void main()
{
	float intensity = dot(lDir,normalize(normal));
	if(gl_FragCoord.z > texture(depthMap,vUV).r)
		discard;

	vec3 L = normalize((view * lDir).xyz);
	vec3 N = normalize(texture(normalMap, vUV).xyz);

	vec3 R = reflect(L, N);
	vec3 E = normalize(view[3].xyz + texture(positionMap,vUV).xyz);
	float sP = 2;

	float lamb = max(0,-dot(L, N));
	float spec = max(0,-dot(E, R));
	if(spec > 0)
			spec = pow(spec, sP);

	//outAlbedo   = texture(albedoMap,   vUV) * lamb * lCol;
	//outSpecular = texture(specularMap, vUV) * spec * lCol;
	//outColor = outAlbedo + outSpecular;

if (intensity > 0.95)
		outcolor = vec4(1.0,0.5,0.5,1.0);
	else if (intensity > 0.5)
		outcolor = vec4(0.6,0.3,0.3,1.0);
	else if (intensity > 0.25)
		outcolor = vec4(0.4,0.2,0.2,1.0);
	else
		outcolor = vec4(0.2,0.1,0.1,1.0);
	
gl_FragColor = outColor;
}