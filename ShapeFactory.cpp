#include "ShapeFactory.h"

void ShapeFactory::initTokens()
{
	_fieldTokens = { {"appearance",[](const std::string& name, const std::string filePart) -> GroupField* {return new GroupField(false, name); }},
					 {"Appearance",[](const std::string& name, const std::string filePart) -> GroupField* {return AppearanceFactory(name).decrypt(filePart); }},
					 {"geometry",[](const std::string& name, const std::string filePart) -> GroupField* {return new GroupField(false, name); }},
					 {"Cone", [](const std::string& name, const std::string& filePart)->GroupField* {return ConeFactory(name).decrypt(filePart); }} };
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
