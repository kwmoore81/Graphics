#pragma once


struct Shader loadShader(const char *vpath, const char *fpath,
	bool depth = true, bool add = false, bool face = true);

struct Texture loadTexture(const char *path);

struct CubeTexture loadCubeMap(const char *path_Xpos, const char *path_Xneg,
	const char *path_Ypos, const char *path_Yneg,
	const char *path_Zpos, const char *path_Zneg);

struct Geometry loadOBJ(const char *path);


unsigned loadALLOBJ(const char *path, Geometry *out, unsigned size = 0);