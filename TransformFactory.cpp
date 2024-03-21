#include "TransformFactory.h"


void TransformFactory::initTokens()
{
	_fieldTokens = { {"translation", [](const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(false, name, _descriptor.parseStringIntoFloatVec(filePart)); }},
					 {"children", [](const std::string& name, const std::string& filePart)->GroupField* {return ChildrenFactory(name).decrypt(filePart);} },
					 {"Shape", [](const std::string& name, const std::string& filePart)->GroupField* {return ShapeFactory(name).decrypt(filePart); }} };
	_fieldDefaultTokens = {};
}

TransformFactory::TransformFactory() {
	initTokens();
}

TransformFactory::TransformFactory(const std::string& name) : AbstractFactory(name) {
	initTokens();
}

TransformFactory::~TransformFactory()
{
}
