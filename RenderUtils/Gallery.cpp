#include "gldecs.h"
#include "crenderutils.h"
#include "Gallery.h"

bool Gallery::makeShader(const char * name, const char * vsource, const char * fsource)
{
	if (!shaders.count(std::string(name)))
	{
		shaders[name] = ::makeShader(vsource, fsource);
		return true;
	}
	else
	{
		fprintf(stderr, "Shader %s already exists!", name);
		return false;
	}
}

bool Gallery::loadShader(const char * name, const char * vpath, const char * fpath)
{
	if (!shaders.count(name))
	{
		shaders[name] = ::loadShader(vpath, fpath);

		if (shaders[name].handle == 0)
		{
			fprintf(stderr, "Shader %s failed to load correctly!\n", name);
			shaders.erase(name);
		}

		fprintf(stderr, "Shader %s successfully loaded!\n", name);
		return true;
	}
	else
	{
		fprintf(stderr, "Shader %s already exists!", name);
		return false;
	}
}

bool Gallery::makeObject(const char * name, const Vertex * verts, size_t vsize, const unsigned * tris, size_t tsize)
{
	objects[name] = makeGeometry(verts, vsize, tris, tsize);
	return true;
}

bool Gallery::loadObjectOBJ(const char * name, const char * path)
{
	objects[name] = loadOBJ(path);
	return true;
}

bool Gallery::makeTexture(const char * name, int w, int h, int f, const unsigned char * p)
{
	textures[name] = ::makeTexture(w, h, f, p);
	return true;
}

bool Gallery::loadTexture(const char * name, const char * path)
{
	textures[name] = ::loadTexture(path);
	return true;
}

const Shader &Gallery::getShader(const char * name)
{
	return shaders.at(name);
}

const Geometry &Gallery::getObject(const char * name)
{
	return objects[name];
}

const Texture &Gallery::getTexture(const char * name)
{
	return textures[name];
}


bool Gallery::term()
{
	// loop through my maps and call my free functions
	for each(auto shader in shaders)
		freeShader(shader.second);

	for each(auto object in objects)
		freeGeometry(object.second);

	return true;
}

bool Gallery::init()
{
	return true;
}