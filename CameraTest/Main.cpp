#include "crenderutils.h"
#include "window.h"

#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

int main()
{
	Window	window;
	window.init(1280, 720);

	glm::mat4 view = glm::lookAt(glm::vec3(5.f, 5.f, 5.f),  // eye
		glm::vec3(0.f, 0.f, 0.f),  // center
		glm::vec3(0.f, 1.f, 0.f)); // up

	glm::mat4 proj = glm::perspective(45.f, 16 / 9.f, 1.f, 100.f);
	glm::mat4 modelC, modelS;


	Geometry soulSpear = loadOBJ("../res/models/soulspear.obj");
	//Geometry bunny = loadOBJ("../res/models/Bunny.obj");
	//Geometry geo = loadOBJ("../res/models/cube.obj");
	Shader   shader = loadShader("../res/shaders/phongVert.txt",
		"../res/shaders/phongFrag.txt");

	Texture tarray[] = { loadTexture("../res/textures/soulspear_diffuse.tga") };

	float time = 0;
	while (window.step())
	{
		time += 0.016f;
		glm::mat4 model = glm::rotate(time, glm::normalize(glm::vec3(0, 1, 0)));
		modelS = glm::translate(glm::vec3(0, cos(time) * 6, 0));
		/*drawPhong(shader, geo, glm::value_ptr(model),
			glm::value_ptr(view),
			glm::value_ptr(proj));

		drawPhong(shader, bunny, glm::value_ptr(model),
			glm::value_ptr(view),
			glm::value_ptr(proj));*/

		drawPhong(shader, soulSpear, glm::value_ptr(modelC),
			glm::value_ptr(view),
			glm::value_ptr(proj), tarray, 1);
	}

	window.term();
	return 0;
}