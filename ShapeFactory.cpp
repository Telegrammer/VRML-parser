#include "ShapeFactory.h"

void ShapeFactory::initTokens()
{
	_fieldTokens.insert({ {"appearance",[](bool isExtern, const std::string& name, const std::string& filePart) -> GroupField* {return new GroupField(isExtern, name); }},
						  {"Appearance",[](bool isExtern, const std::string& name, const std::string& filePart) -> GroupField* {return AppearanceFactory(name).decrypt(isExtern, filePart); }},
						  {"geometry",  [](bool isExtern, const std::string& name, const std::string& filePart) -> GroupField* {return new GroupField(isExtern, name); }},
						  {"Cone",	    [](bool isExtern, const std::string& name, const std::string& filePart) -> GroupField* {return ConeFactory(name).decrypt(isExtern, filePart); }},
						  {"Box",	    [](bool isExtern, const std::string& name, const std::string& filePart) -> GroupField* {return BoxFactory(name).decrypt(isExtern, filePart); }},
						  {"Sphere",	[](bool isExtern, const std::string& name, const std::string& filePart) -> GroupField* {return SphereFactory(name).decrypt(isExtern, filePart); }},
						  {"Cylinder",  [](bool isExtern, const std::string& name, const std::string& filePart) -> GroupField* {return CylinderFactory(name).decrypt(isExtern, filePart); }},
						  {"IndexedLineSet",  [](bool isExtern, const std::string& name, const std::string& filePart) -> GroupField* {return IndexedLineSetFactory(name).decrypt(isExtern, filePart); }},
						  {"IndexedFaceSet",  [](bool isExtern, const std::string& name, const std::string& filePart) -> GroupField* {return IndexedFaceSetFactory(name).decrypt(isExtern, filePart); }}
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
