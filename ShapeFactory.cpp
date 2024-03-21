#include "ShapeFactory.h"

void ShapeFactory::initTokens()
{
	_fieldTokens = { {"geometry",[](const std::string& name, const std::string filePart) -> GroupField* {return new GroupField(false, name, {}); }} };
}

ShapeFactory::ShapeFactory()
{
	initTokens();
}

ShapeFactory::ShapeFactory(const std::string& name) : AbstractFactory(name)
{
	initTokens();
}


ShapeFactory::~ShapeFactory()
{
}
