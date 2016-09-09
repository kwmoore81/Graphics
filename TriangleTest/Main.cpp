#include "crenderutils.h"
#include "window.h"
//#include "Gallery.h"
#include "GLM\ext.hpp"
#include "GLM\glm.hpp"

int main()
{
	Window window;
	//Gallery gallery;

	window.init(1280, 720);
	//gallery.init();
	
	glm::mat4 view = glm::lookAt(glm::vec3(5.f, 5.f, 5.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 proj = glm::perspective(45.f, 16/9.f, 1.f, 100.f);
	glm::mat4 model;

	Geometry geo = loadOBJ("../res/models/cube.obj");
	Shader shader = loadShader("../shaders/phongVert.txt", "../res/shaders/phongFrag.txt");


	/*gallery.loadShader("SIMPLE", "../res/shaders/simpleVert.txt", "../res/shaders/simpleFrag.txt");
	gallery.loadShader("SIMPLE", "../res/shaders/simpleVert.txt", "../res/shaders/simpleFrag.txt");
	gallery.loadObjectOBJ("SPHERE", "../res/models/sphere.obj");*/

	//float time = 0;
	
	while (window.step())
	{
		//drawPhong(shader, geo, glm::value_ptr(model), glm::value_ptr(view), glm::value_ptr(proj));
		/*time += 0.016667f;
		draw(gallery.getShader("SIMPLE"), gallery.getObject("SPHERE"), time);*/
	}

	//gallery.term();
	window.term();

	return 0;
}