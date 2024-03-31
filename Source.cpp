#include <math.h>
#include "FactoryVRML.h"
#include <iostream>


#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <vector>

struct Leaks {
	~Leaks()
	{
		_CrtDumpMemoryLeaks();
	}
} _l;

void print(GroupField* scene) {
}

int main() {
	GroupField* scene = FactoryVRML("scene").decrypt("test.txt");
	size_t depth = 0;
	scene->print(std::cout, depth);
	delete scene;
	return 0;
}