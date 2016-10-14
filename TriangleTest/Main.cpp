
#include "crenderutils.h"
#include "GLM\ext.hpp"
#include "window.h"
#include "Input.h"
#include "GLM\glm.hpp"
#include "Vertex.h"
struct RenderComponent
{

	glm::mat4 model;
Geometry mesh;

Texture norm, diff, spec;

Shader  shader;
Framebuffer fb;
};

struct DirectionalLight
{
	glm::vec3 dir, color;
	float size;
	glm::mat4 getMatrix()
	{
		return glm::ortho<float>(-size, size, -size, size, -size, size)
			* glm::lookAt(-dir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	}
};

void main()
{
	Window context;
	Input input;
	context.init(1280, 720);
	input.init(context);

	Geometry quad = makeGeometry(quad_verts, 4, quad_tris, 6);
	Geometry mech1 = loadOBJ("../res/models/mech1.obj");
	Geometry cube = loadOBJ("../res/models/cube.obj");
	
	Texture mech_normal = loadTexture("../res/textures/light_grey.tga");
	Texture mech_diffuse = loadTexture("../res/textures/light_grey.tga");
	Texture mech_specular = loadTexture("../res/textures/light_grey.tga");

	const unsigned char norm_pixels[4] = { 127, 127, 255, 255 };
	Texture vertex_normals = makeTexture(1, 1, 4, norm_pixels);

	const unsigned char white_pixels[4] = { 255, 255, 255, 255 };
	Texture white = makeTexture(1, 1, 4, white_pixels);

	Shader qdraw = loadShader("../res/shaders/quad.vert", "../res/shaders/quad.frag", false);
	Shader gpass = loadShader("../res/shaders/gpass.vert", "../res/shaders/gpass.frag");
	Shader sky = loadShader("../res/shaders/sky.vert", "../res/shaders/sky.frag", false, false, false);
	// Using Light pass shader designed for shadows.
	// Note that shadow pass can disable face-culling for some back-shadow improvements.
	Shader spass = loadShader("../res/shaders/spass.vert", "../res/shaders/spass.frag", true, false, false);
	Shader lpass = loadShader("../res/shaders/lspass.vert", "../res/shaders/lspass.frag", false, true);
	Shader cell = loadShader("../res/shaders/cell.vert", "../res/shaders/cell.frag");

	Framebuffer screen = { 0, 1280, 720 };
	//Framebuffer skyframe = { 0, 1280, 720 };

	bool flTex[] = { false, true, false, true }; // colors don't need floats, but position/normal should use it.
	Framebuffer gframe = makeFramebuffer(1280, 720, 4, flTex);
	Framebuffer lframe = makeFramebuffer(1280, 720, 3);
	Framebuffer skyframe = makeFramebuffer(1280, 720, 2);

	// Temporary shadow framebuffer. Will be cleared and reused by each light!
	// Its RESOLUTION WILL GREATLY EFFECT THE QUALITY. Try playing around with high/low res.
	Framebuffer sframe = makeFramebuffer(1024, 1024, 0);

	CubeTexture cbmp = loadCubeMap("../res/textures/icyhell_rt.tga", "../res/textures/icyhell_lf.tga",
		                           "../res/textures/icyhell_up.tga", "../res/textures/icyhell_dn.tga",
		                           "../res/textures/icyhell_bk.tga", "../res/textures/icyhell_ft.tga");

	// Camera information
	glm::mat4 camView = glm::lookAt(glm::vec3(0, -10, 15), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 camProj = glm::perspective(45.f, 1280.f / 720, 1.f, 100.f);

	// Model Matrices
	glm::mat4 mechModel = glm::rotate(1.f, glm::vec3(0.6f, 0.5f, 0.0f)) * glm::translate(glm::vec3(0, -5, 4));
	glm::mat4 sphereModel = glm::translate(glm::vec3(-10.0f, 0.5f, 5.0f));

	// Light Matrices and data
	// They can all use the same projection matrix...
	glm::mat4 lightProj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);

	glm::mat4   redView = glm::lookAt(glm::normalize(-glm::vec3(1, -1, -1)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::vec4   redColor = glm::vec4(0.184314, 0.309804f, 0.309804, 1);

	glm::mat4 greenView = glm::lookAt(glm::normalize(-glm::vec3(1, 1, -1)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::vec4 greenColor = glm::vec4(0.184314, 0.184314, 0.309804, 1);

	glm::mat4 blueView = glm::lookAt(glm::normalize(-glm::vec3(-1, -1, 1)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::vec4 blueColor = glm::vec4(0.184314f, 0.309804f, 0.309804f, 1);

	glm::mat4 yellowView = glm::lookAt(glm::normalize(-glm::vec3(-1, 1, 1)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::vec4 yellowColor = glm::vec4(0.184314f, 0.309804f, 0.309804f, 1);
	float time = 0;

	while (context.step())
	{
		clearFramebuffer(screen);
		time += 0.001f;
		input.step();
		// Geometry Pass

		clearFramebuffer(gframe);
		
		tdraw(gpass, mech1, gframe, mechModel, camView, camProj, mech_diffuse, mech_normal, mech_specular);
		
		// Light pass
		clearFramebuffer(lframe);

		// RED LIGHT

		// Shadow PrePass
		clearFramebuffer(sframe);
		/*tdraw(cell, mech1, sframe, mechModel, redView, lightProj);
		tdraw(lpass, quad, lframe, camView,
			gframe.colors[0], gframe.colors[1], gframe.colors[2], gframe.colors[3],
			sframe.depth, redColor, redView, lightProj);*/

		tdraw(lpass, quad, lframe, camView,
			gframe.colors[0], gframe.colors[1], gframe.colors[2], gframe.colors[3],
			sframe.depth, redColor, redView, lightProj);
		// Green light

		// Reuse the shadow pass
		clearFramebuffer(sframe);
		/*tdraw(cell, mech1, sframe, mechModel, greenView, lightProj);
		tdraw(lpass, quad, lframe, camView,
			gframe.colors[0], gframe.colors[1], gframe.colors[2], gframe.colors[3],
			sframe.depth, greenColor, greenView, lightProj);*/

		tdraw(lpass, quad, lframe, camView,
			gframe.colors[0], gframe.colors[1], gframe.colors[2], gframe.colors[3],
			sframe.depth, greenColor, greenView, lightProj);

		clearFramebuffer(sframe);

		tdraw(lpass, quad, lframe, camView,
			gframe.colors[0], gframe.colors[1], gframe.colors[2], gframe.colors[3],
			sframe.depth, blueColor, blueView, lightProj);

		clearFramebuffer(sframe);

		tdraw(lpass, quad, lframe, camView,
			gframe.colors[0], gframe.colors[1], gframe.colors[2], gframe.colors[3],
			sframe.depth, yellowColor, yellowView, lightProj);

		clearFramebuffer(skyframe);

		glm::mat4 skyBox = camProj * glm::scale(glm::vec3(5, 5, 5)) * glm::rotate(time, glm::vec3(0, 1, 0));
		tdraw(sky, cube, skyframe, skyBox, cbmp);
		
		glm::mat4 mod = glm::translate(glm::vec3(0.0f, 0.0f, 0));
		tdraw(qdraw, quad, screen, lframe.colors[0], mod, skyframe.colors[0]);
		
	
	}

	context.term();
}