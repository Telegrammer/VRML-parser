#include "FactoryVRML.h"


void FactoryVRML::initTokens()
{
	_fieldTokens.insert({ {"Transform", [](bool isExtern, const std::string& name, const std::string& filePart)-> GroupField* {return TransformFactory(name).decrypt(isExtern, filePart); }},
						  {"Shape", [](bool isExtern, const std::string& name, const std::string& filePart) -> GroupField* {return ShapeFactory(name).decrypt(isExtern, filePart); }} });
}

FactoryVRML::FactoryVRML() {
	initTokens();
}


FactoryVRML::FactoryVRML(const std::string& name) : AbstractFactory(name) {
	initTokens();
}

FactoryVRML::~FactoryVRML() {
}

GroupField* FactoryVRML::decrypt(bool isExtern, const std::string& fileData)
{
	GroupField* scene = new GroupField(isExtern, _objectName, {});
	std::string file = _descriptor.readFile(fileData);
	_descriptor.decrypt(file, scene, _fieldTokens);
	return scene;
}
