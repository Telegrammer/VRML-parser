#include <math.h>
#include <iostream>

#include "FactoryVRML.h"
#include "Field.h"
#include "Vector3f.h"
#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <vector>
#include <string>

struct Leaks {
	~Leaks()
	{
		_CrtDumpMemoryLeaks();
	}
} _l;

int main() {
	char* c = new char('c');
	FactoryVRML sceneFactory("scene");
	GroupField* scene = sceneFactory.decrypt(true, "MBA_N.wrl");
	size_t depth = 0;
	scene->print(std::cout, depth);
	delete scene;
	DescriptorVRML::deleteInstance();
	return 0;
}