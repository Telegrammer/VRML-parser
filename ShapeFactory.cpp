#include "ShapeFactory.h"

void ShapeFactory::initTokens()
{
	_fieldTokens = { {"appearance",[](const std::string& name, const std::string filePart) -> GroupField* {return AppearanceFactory(name).decrypt(filePart); }},
					 {"Appearance",[](const std::string& name, const std::string filePart) -> GroupField* {return AppearanceFactory(name).decrypt(filePart); }},
					 {"geometry",[](const std::string& name, const std::string filePart) -> GroupField* {return GeometryFactory(name).decrypt(filePart); }},
					 {"Cone", [](const std::string& name, const std::string& filePart)->GroupField* {return new GroupField(false, name, {}); }} };
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
