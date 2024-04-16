#include "FactoryVRML.h"


void FactoryVRML::initTokens()
{
	_fieldTokens = { {"Transform", [](const std::string& name, const std::string& filePart)-> GroupField* {return TransformFactory(name).decrypt(filePart); }},
					 {"Shape", [](const std::string& name, const std::string& filePart) -> GroupField* {return ShapeFactory(name).decrypt(filePart); }} };
}

FactoryVRML::FactoryVRML() {
	initTokens();
}


FactoryVRML::FactoryVRML(const std::string& name) : AbstractFactory(name) {
	initTokens();
}

FactoryVRML::~FactoryVRML() {
}

GroupField* FactoryVRML::decrypt(const std::string& fileData)
{
	GroupField* scene = new GroupField(false, _objectName, {});
	std::string file = _descriptor.readFile(fileData);
	_descriptor.decrypt(file, scene, _fieldTokens);
	return scene;
}
