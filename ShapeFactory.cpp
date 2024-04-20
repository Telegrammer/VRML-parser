#include "ShapeFactory.h"

void ShapeFactory::initTokens()
{
	_fieldTokens.insert({ {"appearance",[](const std::string& name, const std::string& filePart) -> GroupField* {return new GroupField(false, name); }},
						  {"Appearance",[](const std::string& name, const std::string& filePart) -> GroupField* {return AppearanceFactory(name).decrypt(filePart); }},
						  {"geometry",  [](const std::string& name, const std::string& filePart) -> GroupField* {return new GroupField(false, name); }},
						  {"Cone",	    [](const std::string& name, const std::string& filePart) -> GroupField* {return ConeFactory(name).decrypt(filePart); }},
						  {"Box",	    [](const std::string& name, const std::string& filePart) -> GroupField* {return BoxFactory(name).decrypt(filePart); }},
						  {"Sphere",	[](const std::string& name, const std::string& filePart) -> GroupField* {return SphereFactory(name).decrypt(filePart); }},
						  {"Cylinder",  [](const std::string& name, const std::string& filePart) -> GroupField* {return CylinderFactory(name).decrypt(filePart); }}
	});
	_fieldDefaultTokens.insert({
		{"appearance", [](const std::string& name) -> GroupField* {return new GroupField(false, name); }},
		{"geometry",   [](const std::string& name) -> GroupField* {return new GroupField(false, name); }}
	});
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
