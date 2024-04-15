#include "AppearanceFactory.h"

void AppearanceFactory::initTokens()
{
	_fieldTokens = { {"material",[](const std::string& name, const std::string filePart) -> GroupField* {return new GroupField(false, name); }},
					 {"Material",[](const std::string& name, const std::string filePart) -> GroupField* {return MaterialFactory(name).decrypt(filePart); }} };
}

AppearanceFactory::AppearanceFactory() : AbstractFactory()
{
	initTokens();
}

AppearanceFactory::AppearanceFactory(const std::string& name) : AbstractFactory(name)
{
	initTokens();
}

AppearanceFactory::~AppearanceFactory() 
{
}
