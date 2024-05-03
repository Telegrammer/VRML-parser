#include <math.h>
#include <iostream>

#include "DescriptorVRML.h"
#include "Field.h"
#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <vector>

struct Leaks {
	~Leaks()
	{
		_CrtDumpMemoryLeaks();
	}
} _l;

int main() {
	char* c = new char('c');
	//GroupField* scene = FactoryVRML("scene").decrypt(true, "test.txt");
	//size_t depth = 0;
	//Field<bool>* scene = new Field<bool>(true, "scene", true);
	////scene->print(std::cout, depth);
	return 0;
}