#define GLEW_STATIC

#include "GLEW\glew.h"
#include "Vertex.h"
#include "crenderutils.h"

Geometry makeGeometry(const Vertex * verts, size_t vsize, const unsigned int * tris, size_t tsize)
{
	Geometry retval;
	retval.size = tsize;

	//Define the variables
	glCreateBuffers(1, &retval.vbo);  //Store vertices
	glCreateBuffers(1, &retval.ibo);  //Store indices
	glCreateVertexArrays(1, &retval.vao); //Store attribute information
	//Scope the variables
	glBindVertexArray(retval.vao);
	glBindBuffer(GL_ARRAY_BUFFER, retval.ibo); //scope our vertices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retval.ibo); //triangle is scoped
	//Initialize the variables
	new float[4];
	glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(Vertex), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tsize * sizeof(unsigned), tris, GL_STATIC_DRAW);
	
	//Attributes let us tell openGL how the memory is load out
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//index of the attribute, number of elements, type, normalized?, size of vertex, offset
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)16);
	
	//unscope the variables
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return retval;
}

void freeGeometry(Geometry &geo)
{
	glDeleteBuffers(1, &geo.vbo);
	glDeleteBuffers(1, &geo.ibo);
	glDeleteVertexArrays(1, &geo.vao);
	geo = { 0, 0, 0, 0 };
}

Shader makeShader(const char * vsource, const char * fsource)
{
	Shader retval;
	//create our variables
	retval.handle = glCreateProgram();
	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);
	//initialize out variables
	glShaderSource(vs, 1, &vsource, 0);
	glShaderSource(fs, 1, &fsource, 0);
	//compile the shaders
	glCompileShader(vs);
	glCompileShader(fs);
	//like the shaders into a single program
	glAttachShader(retval.handle, vs);
	glAttachShader(retval.handle, fs);
	glLinkProgram(retval.handle);
	//no longer need these! Their functionality has been eaten by the program.
	glDeleteShader(vs);
	glDeleteShader(fs);

	return retval;
}

void freeShader(Shader &);