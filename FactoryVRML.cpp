#include "FactoryVRML.h"


void FactoryVRML::initTokens()
{
	_fieldTokens.insert({ {"Transform", [](bool isExtern, const std::string& name, const std::string& filePart)-> GroupField* {return TransformFactory(name).decrypt(isExtern, filePart); }},
						  {"Shape", [](bool isExtern, const std::string& name, const std::string& filePart) -> GroupField* {return ShapeFactory(name).decrypt(isExtern, filePart); }},
						  {"Viewpoint", [](bool isExtern, const std::string& name, const std::string& filePart) -> GroupField* {return ViewpointFactory(name).decrypt(isExtern, filePart); }},
						  {"WorldInfo", [](bool isExtern, const std::string& name, const std::string& filePart) -> GroupField* {return WorldInfoFactory(name).decrypt(isExtern, filePart); }},
						  {"Background", [](bool isExtern, const std::string& name, const std::string& filePart) -> GroupField* {return BackgroundFactory(name).decrypt(isExtern, filePart); }},
						  {"Group", [](bool isExtern, const std::string& name, const std::string& filePart) -> GroupField* {return GroupFactory(name).decrypt(isExtern, filePart); }}
	});
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
	std::string file = _descriptor->readFile(fileData);
	int fin = file.size();
	std::regex wordsRegex("(\\b\\w+\\b|\\{|\\[)");
	std::sregex_iterator wordsBegin = std::sregex_iterator(file.begin(), file.end(), wordsRegex);
	_descriptor->setWordsBegin(wordsBegin, file);
	_descriptor->decrypt(file, scene, _fieldTokens);
	return scene;
}
