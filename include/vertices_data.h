#ifndef VERT_DATA_H
#define VERT_DATA_H

#include <cstddef>

// constexpr size_t cubeVerticesTCSize 		= 36 * 5 * sizeof(float);
// constexpr size_t cubeVerticesSize 			= 36 * 3 * sizeof(float);
// constexpr size_t quadVerticesSize 			= 6 * 2 * sizeof(float);
// constexpr size_t unitQuadVerticesSize 		= 6 * 2 * sizeof(float);
// constexpr size_t unitQuadVerticesTCSize 	= 6 * 4 * sizeof(float); 
// constexpr size_t unitQuadVerticesTCNCSize	= 6 * 7 * sizeof(float);

extern size_t cubeVerticesTCSize;
extern size_t cubeVerticesSize;
extern size_t quadVerticesSize;
extern size_t unitQuadVerticesSize;
extern size_t unitQuadVerticesTCSize;
extern size_t unitQuadVerticesTCNCSize;



extern float cubeVerticesTC[];
extern float cubeVertices[];
extern float quadvertices[];
extern float unitQuadVertices[];
extern float unitQuadVerticesTC[];
extern float unitQuadVerticesTCNC[];


#endif