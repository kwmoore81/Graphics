#pragma once
#include <glew\glew.h>
#include <SDL.h>

void setupCubeMap(GLuint& texture);

void setupCubeMap(GLuint& texture, SDL_Surface *xpos, SDL_Surface *xneg, SDL_Surface *ypos, SDL_Surface *yneg, SDL_Surface *zpos, SDL_Surface *zneg);

void deleteCubeMap(GLuint& texture);
