#pragma once
#include <string>
#include <map>
#include "globjects.h"
#include "Vertex.h"

//Render Object: A thing tht we render, I.e. Geometry, Mesh, Polygon
//Shader Program: Pipeline of shader scripts, that divide and fill the sceen.
class Gallery
{
	std::map<std::string, Geometry> objects;
	std::map<std::string, Shader> shaders;

public:
	//Shader makeShader(vsource, fsource)

	bool makeShader(const char * name, const char* vsource, const char *fsource);
	bool loadShader(const char* name, const char* vpath, const char *fpath);
	bool makeObject(const char * bane, const Vertex *verts, size_t vsize, const unsigned *tris, size_t tsize);
	bool loadObjectOBJ(const char *name, const char *path);

	const Geometry &getObject(const char *name);
	const Shader &getShader(const char *name);

	bool init();
	bool term();

};