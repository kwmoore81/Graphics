#pragma once
#include "globjects.h"


/*

	Generate a grid

*/

Geometry genGrid(unsigned sqr, float dim);

/*

	Make some noise!
		On a texture

*/

Texture genNoise(unsigned sqr, unsigned octaves);
