#pragma once


struct Shader loadShader(const char *vpath, const char *fpath,
	bool depth = true, bool add = false, bool face = true);

struct Texture loadTexture(const char *path);

struct Geometry loadOBJ(const char *path);