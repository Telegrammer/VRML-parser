#include "ChildrenFactory.h"

void ChildrenFactory::initTokens()
{
	_fieldTokens.insert({ {"Shape", [](bool isExtern, const std::string& name, const std::string& filePart)-> GroupField* {return ShapeFactory(name).decrypt(isExtern, filePart); }},
						  {"Group", [](bool isExtern, const std::string& name, const std::string& filePart)-> GroupField* {return GroupFactory(name).decrypt(isExtern, filePart); }},
						  {"Transform", [](bool isExtern, const std::string& name, const std::string& filePart)-> GroupField* {return GroupFactory(name).decrypt(isExtern, filePart); }} });
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
