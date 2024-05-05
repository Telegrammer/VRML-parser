#include "AbstractFactory.h"

void AbstractFactory::initCustomFieldTokens()
{
	_fieldTokens = {};
	_fieldDefaultTokens = { };
}

AbstractFactory::AbstractFactory() : _objectName("untitled") {
	initCustomFieldTokens();
	_descriptor = DescriptorVRML::getInstance();
}

AbstractFactory::AbstractFactory(const std::string& name) : _objectName(name) {
	initCustomFieldTokens();
	_descriptor = DescriptorVRML::getInstance();
}

AbstractFactory::~AbstractFactory() {
	_fieldDefaultTokens.clear();
	_fieldTokens.clear();
}

GroupField* AbstractFactory::decrypt(bool isExtern, const std::string& fileData)
{
	GroupField* field = new GroupField(isExtern, _objectName, {});
	_descriptor->decrypt(fileData, field, _fieldTokens);
	std::set<std::string> names = field->getNames();
	for (auto it = _fieldDefaultTokens.begin(); it != _fieldDefaultTokens.end(); it++) {
		if (names.find(it->first) == names.end()) {
			field->addFieldPtr(it->second(it->first));
		}
	}
	return field;
}
