#include "AbstractFactory.h"


DescriptorVRML AbstractFactory::_descriptor = DescriptorVRML();

AbstractFactory::AbstractFactory() : _objectName("untitled") {
}

AbstractFactory::AbstractFactory(const std::string& name) : _objectName(name) {}

AbstractFactory::~AbstractFactory() {}

GroupField* AbstractFactory::decrypt(const std::string& fileData)
{
	GroupField* field = new GroupField(false, _objectName, {});
	_descriptor.decrypt(fileData, field, _fieldTokens);
	return field;
}
