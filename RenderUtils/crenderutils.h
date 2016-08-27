#pragma once

#include "globjects.h"


Geometry makeGeometry(const struct Vertex *verts, size_t vsize, const unsigned int *tris, size_t tsize);

void freeGeometry(Geometry &);

Geometry loadOBJ(const char *path);

Shader makeShader(const char *vsource, const char *fsource);

Shader loadShader(const char *vpath, const char *fpath);

void freeShader(Shader &);

void draw(const Shader &, const Geometry &);

void draw(const Shader &shader, const Geometry &geometry, float time);