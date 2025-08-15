#include "vertices_data.h"

float cubeVerticesTC[] = {
	// positions          // texture Coords
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};


float cubeVertices[] = {       
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

float quadvertices[]{
	-1.0f, -1.0f,
	 1.0f, -1.0f,
	 1.0f,  1.0f,
	 1.0f,  1.0f,
	-1.0f,  1.0f,
	-1.0f, -1.0f
};

float unitQuadVertices[]{
	-0.5f, -0.5f,
	 0.5f, -0.5f,
	 0.5f,  0.5f,
	 0.5f,  0.5f,
	-0.5f,  0.5f,
	-0.5f, -0.5f
};

// float unitQuadVerticesTC[]{
// 	-0.5f, -0.5f, 0.0f, 0.0f,
// 	 0.5f, -0.5f, 1.0f, 0.0f,
// 	 0.5f,  0.5f, 1.0f, 1.0f,
// 	 0.5f,  0.5f, 1.0f, 1.0f,
// 	-0.5f,  0.5f, 0.0f, 1.0f,
// 	-0.5f, -0.5f, 0.0f, 0.0f
// };

float unitQuadVerticesTC[] = {
    // x, y      // u, v
    -0.5f, -0.5f,  0.0f, 0.0f,  // bottom left
     0.5f, -0.5f,  1.0f, 0.0f,  // bottom right
     0.5f,  0.5f,  1.0f, 1.0f,  // top right

     0.5f,  0.5f,  1.0f, 1.0f,  // top right
    -0.5f,  0.5f,  0.0f, 1.0f,  // top left
    -0.5f, -0.5f,  0.0f, 0.0f   // bottom left
};



float unitQuadVerticesTCNC[] = {
    // x, y      // u, v        //normal
    -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,// bottom left
     0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,// bottom right
     0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,// top right

     0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,// top right
    -0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,// top left
    -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,// bottom left
};


size_t cubeVerticesTCSize       = sizeof(cubeVerticesTC);
size_t cubeVerticesSize         = sizeof(cubeVertices);
size_t quadVerticesSize         = sizeof(quadvertices);
size_t unitQuadVerticesSize     = sizeof(unitQuadVertices);
size_t unitQuadVerticesTCSize   = sizeof(unitQuadVerticesTC);
size_t unitQuadVerticesTCNCSize = sizeof(unitQuadVerticesTCNC);

