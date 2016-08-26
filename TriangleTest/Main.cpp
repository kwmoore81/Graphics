#include "crenderutils.h"
#include "window.h"
#include "Vertex.h"
// This is the develop branch!

int main()
{
	Window window;
	window.init();

	Vertex vert[3] = { 0, .5f, 0, 1, 1, 0, 0, .5f, -.5f, 0, 1, 0, 1, 0, 1, -.5f, -.5f, 0, 1, 0, 0, 1, 1 };
	
	unsigned tris[3] = {0, 1, 2};

	const char vsource[] = "#version 330\n"
		                   "layout(location = 0)in vec4 position;"
		                   "layout(location = 1)in vec4 color;"
		                   "out vec4 vColor;"
		                   "void main() {cColor = color; gl_Position = position; } ";
	
	const char fsource[] = "#version 150\n"
		                   "in vec4 vColor;"
		                   "out vec4 outColor;"
		                   "void main() { outColor = vec4(1.000, 0.843, 0.0000, 1.0) - vColor; } ";
	
	Geometry geometry = makeGeometry(vert, 3, tris, 3);
	Shader shader = makeShader(vsource, fsource);

	while (window.step())
	{
		draw(shader, geometry);
	}

	window.term();

	return 0;
}