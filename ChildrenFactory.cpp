#include "ChildrenFactory.h"

void ChildrenFactory::initTokens()
{
	_fieldTokens = { {"Shape", [](const std::string& name, const std::string& filePart)-> GroupField* {return ShapeFactory(name).decrypt(filePart); }} };
}

ChildrenFactory::ChildrenFactory()
{
	initTokens();
}

ChildrenFactory::ChildrenFactory(const std::string& name) : AbstractFactory(name)
{
	initTokens();
}

ChildrenFactory::~ChildrenFactory()
{
}
