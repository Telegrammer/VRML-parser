#include "AbstractFactory.h"


DescriptorVRML AbstractFactory::_descriptor = DescriptorVRML();

void AbstractFactory::initCustomFieldTokens()
{
	_fieldTokens = {};
	_fieldDefaultTokens = { {"LOL", [](const std::string& name) -> GroupField* {return new GroupField(false, name); }} };
}

AbstractFactory::AbstractFactory() : _objectName("untitled") {
	initCustomFieldTokens();
}

AbstractFactory::AbstractFactory(const std::string& name) : _objectName(name) {
	initCustomFieldTokens();
}

AbstractFactory::~AbstractFactory() {}

GroupField* AbstractFactory::decrypt(const std::string& fileData)
{
	GroupField* field = new GroupField(false, _objectName, {});
	_descriptor.decrypt(fileData, field, _fieldTokens);
	std::set<std::string> names = field->getNames();
	for (auto it = _fieldDefaultTokens.begin(); it != _fieldDefaultTokens.end(); it++) {
		if (names.find(it->first) == names.end()) {
			field->addFieldPtr(it->second(it->first));
		}
	}
	return field;
}
