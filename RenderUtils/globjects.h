#pragma once
struct Geometry
{
	unsigned vbo, ibo, vao, size;
	// Vertex Buffer Object : an array of vertices
	// Index Buffer Object  : an array of indices (triangles)
	// Vertex Array Object  : Groups the two with some formatting
	// size                 : number of triangles.
};


struct Shader
{
	unsigned handle;
};


struct Texture
{

	unsigned handle;
	unsigned width, height, format;

};