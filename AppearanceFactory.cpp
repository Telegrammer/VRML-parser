#include "AppearanceFactory.h"

void AppearanceFactory::initTokens()
{
	_fieldTokens.insert({ {"material",[](const std::string& name, const std::string filePart) -> GroupField* {return new GroupField(false, name); }},
						  {"Material",[](const std::string& name, const std::string filePart) -> GroupField* {return MaterialFactory(name).decrypt(filePart); }} });

	_fieldDefaultTokens.insert(
		{ {"material",[](const std::string& name) -> GroupField* {return new GroupField(false, name); }},
		  {"texture", [](const std::string& name) -> GroupField* {return new GroupField(false, name); }},
		  {"textureTransform", [](const std::string& name) -> GroupField* {return new GroupField(false, name); }} });

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
