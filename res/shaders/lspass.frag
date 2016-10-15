#version 430

// Vertex Data
in vec2 vUV;

//uniform float visibility = 1;
// Camera Data
layout(location = 0) uniform mat4 view;

// Gpass Data
layout(location = 1) uniform sampler2D albedoMap;
layout(location = 2) uniform sampler2D normalMap;
layout(location = 3) uniform sampler2D specularMap;
layout(location = 4) uniform sampler2D positionMap;

// Shadow Pass Data
layout(location = 5) uniform sampler2D shadowMap;
uniform float shadowBias = 0.1f;

// Light Data
layout(location = 6) uniform vec4 lCol;
layout(location = 7) uniform mat4 lightView; // lightDirection is the forward now!
layout(location = 8) uniform mat4 lightProj;

// Framebuffer Outputs
layout(location = 0) out vec4 outColor;
layout(location = 1) out vec4 outAlbedo;
layout(location = 2) out vec4 outSpecular;


// Simple matrix that converts from clip space (-1,1) to UV space (0,1)
uniform mat4 clipToUV = mat4(0.5f, 0.0f, 0.0f, 0.0f,
							 0.0f, 0.5f, 0.0f, 0.0f,
							 0.0f, 0.0f, 0.5f, 0.0f,
							 0.5f, 0.5f, 0.5f, 1.0f);

void main()
{		 
	vec3 L = normalize((view * lightView[2]).xyz);
	vec3 N = normalize(texture(normalMap, vUV).xyz);
	vec4 P = texture(positionMap,vUV);
	
	//vec4 intensity = dot(lightView, normalize(texture(normalMap, vUV)));
	float ambientStrength = 0.1;
	vec4 ambient = ambientStrength * lCol;
	

	if(P.a == 0)
		discard;

	/////////////////////////////////////////////////////
	/////// Shadow Map calculations

	// Space transfomrations!
	// VIEW -> WORLD -> LIGHT -> CLIP -> UV
	vec4 sUV = clipToUV * lightProj * lightView * inverse(view) * vec4(P.xyz,1);

	float alp = 1.0f;

	// compare the sampled Z value against our projected Z position.
	// if the sample is closer, we don't draw in the shadow.
	if(texture(shadowMap, sUV.xy).r < sUV.z - shadowBias)
		alp = 0.0f;

//Lighting 

	vec3 R = reflect(L , N);
	vec3 E = normalize(view[3].xyz + P.xyz);
	float sP = 2;

	float lamb = max(0,-dot(L, N));
	float spec = max(0,-dot(E , R * 5));
	if(spec > 0)
			spec = pow(spec, sP);


	outAlbedo   = texture(albedoMap,   vUV) * lamb * lCol * alp;
	outSpecular = texture(specularMap, vUV) * spec * lCol * alp;
	vec4 ambientResult = ambient * texture(albedoMap, vUV);
	vec4 outAmbient = ambientResult;

	vec4 baseOutColor = outAlbedo + outSpecular + outAmbient;

if (lamb > 0.95)
		outColor =  baseOutColor + vec4(1.0,0.5,0.5,1.0);
	else if (lamb > 0.5)
		outColor = baseOutColor + vec4(0.6,0.3,0.3,1.0);
	else if (lamb > 0.25)
		outColor = baseOutColor + vec4(0.4,0.2,0.2,1.0);
	else
		outColor = baseOutColor + vec4(0.2,0.1,0.1,1.0);
	
	outColor.a = alp;
	

	
}