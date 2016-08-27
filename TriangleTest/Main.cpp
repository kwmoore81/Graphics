#include "crenderutils.h"
#include "window.h"
#include "Gallery.h"


int main()
{
	Window window;
	Gallery gallery;

	window.init(600, 600);
	gallery.init();
	
	gallery.loadShader("SIMPLE", "../res/shaders/simpleVert.txt", "../res/shaders/simpleFrag.txt");
	//gallery.loadShader("SIMPLE", "../res/shaders/simpleVert.txt", "../res/shaders/simpleFrag.txt");
	gallery.loadObjectOBJ("SPHERE", "../res/models/sphere.obj");

	float time = 0;
	
	while (window.step())
	{
		time += 0.016667f;
		draw(gallery.getShader("SIMPLE"), gallery.getObject("SPHERE"), time);
	}

	gallery.term();
	window.term();

	return 0;
}