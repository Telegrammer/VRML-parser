#pragma once
#include "AbstractField.h"
#include "DescriptorVRML.h"
#include "Field.h"


class AbstractFactory {
protected:
	static DescriptorVRML _descriptor;

	std::string _objectName;
	std::map<std::string, std::function<AbstractField* (const std::string& name, const std::string& body)>> _fieldTokens;
	std::map<std::string, std::function<AbstractField* (const std::string& name, const std::string& body)>> _fieldDefaultTokens;

	virtual void initTokens() = 0;
	AbstractFactory();
	AbstractFactory(const std::string& name);
	AbstractFactory(const AbstractFactory& rhs) = delete;
	AbstractFactory& operator=(const AbstractFactory& rhs) = delete;
public:
	virtual ~AbstractFactory() = 0;
	virtual GroupField* decrypt(const std::string& fileData);
};