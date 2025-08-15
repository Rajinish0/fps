#ifndef FUNCS_GUARD
#define FUNCS_GUARD
#include <iostream>
#include <string>
#include "mesh.h"

namespace funcs {
	unsigned int TextureFromFile(const std::string& path, std::string directory);
	unsigned int loadCubeMap(std::vector<std::string> faces);
	bool rayCollidesSphere(glm::vec3 rPos, glm::vec3 rDir, glm::vec3 spherePos, float spRad);
	Mesh genSphere();
	Mesh genTorus(); // or donut?
	template<typename T>
	T clamp(T val, T lowerb, T upperb){
		if (val < lowerb) return lowerb;
		if (val > upperb) return upperb;
		return val;
	}
}

#endif
