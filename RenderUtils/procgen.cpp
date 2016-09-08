#include "procgen.h"
#include "crenderutils.h"
#include"Vertex.h"
#include "GLM\glm.hpp"

Geometry genGrid(unsigned sqr, float dim)
{
	unsigned vsize = sqr*sqr;
	unsigned tsize = (sqr-1)*(sqr-1)*6;
	Vertex  *verts = new Vertex[vsize];
	unsigned *tris = new unsigned[tsize];
	
	for(int r = 0; r < sqr; ++ r)
		for (int c = 0; c < sqr; ++c)
		{
			verts[r * sqr + c].position = glm::vec4((c / (sqr - 1.f) - .5f)*dim, 0, (r / (sqr - 1.f) - .5f)*dim, 1);
			verts[r * sqr + c].texCoord = glm::vec2(c / (sqr - 1.f), r / (sqr - 1.f));
			verts[r * sqr + c].normal = glm::vec4(0, 1, 0, 0);
		}
	//generate an array of vertices

	unsigned index = 0;


	for (int r = 0; r<sqr; ++r)
		for (int c = 0; c < sqr; ++c)
		{
			tris[index++] = r * sqr + c; //bottom left corner
			tris[index++] = (r + 1) * sqr + c;  //bottom right corner
			tris[index++] = r + 1 * sqr + (c+1); //top right corner

			tris[index++] = r * sqr + c; //bottom left corner
			tris[index++] = (r + 1) *sqr + (c + 1);  //top right corner
			tris[index++] = r + 1 * sqr + (c + 1); //top left corner
		}



	//generate an array of triangles
	Geometry retval = makeGeometry(verts, vsize, tris, tsize);

	delete[] verts;
	delete[] tris;

	return retval;
}

#include "GLM\gtc\noise.hpp"

Texture genNoise(unsigned sqr, unsigned octaves)
{
	float *noise = new float[sqr*sqr];
	float scale = 1.0f / sqr * 3.f;

	for(int x = 0; x < sqr; ++x)
		for (int y = 0; y < sqr; ++y)
		{
			float amplitude = 1.f;
			float persistence = 0.25f;
			noise[y*sqr + x] = 0;
			//noise[y*sqr + x] = glm::perlin(glm::vec2(x.y)*scale) * 0.5f + 0.5f;
			for (int o = 0; o < octaves; ++o)
			{
				float freq = powf(2, o);
				float data = glm::perlin(glm::vec2((float)x, (float)y)*scale*freq) * 0.5f + 0.5f;
				noise[y*sqr + x] += data *amplitude;
				amplitude *= persistence;
			}
		}

	Texture retval = makeTextureF(sqr, noise);
	delete[] noise;
	return retval;
}
