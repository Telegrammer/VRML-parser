#include "ConeFactory.h"

void ConeFactory::initTokens()
{
	_fieldTokens.insert({
		  {"radius", [](const std::string& name, const std::string& filePart)->Field<float>*{return new Field<float>(false, name, _descriptor.parseStringIntoFloat(filePart)); }},
		  {"height", [](const std::string& name, const std::string& filePart)->Field<float>*{return new Field<float>(false, name, _descriptor.parseStringIntoFloat(filePart)); }},
		  {"side",   [](const std::string& name, const std::string& filePart)->Field<bool>*{return new Field<bool>(false, name, _descriptor.parseStringIntoBool(filePart)); }},
		  {"bottom", [](const std::string& name, const std::string& filePart)->Field<bool>*{return new Field<bool>(false, name, _descriptor.parseStringIntoBool(filePart)); }}
	});
	_fieldDefaultTokens.insert({
		{"radius", [](const std::string& name) -> Field<float>*{return new Field<float>(false, name, 1.0f); }},
		{"height", [](const std::string& name) -> Field<float>*{return new Field<float>(false, name, 2.0f); }},
		{"side",   [](const std::string& name) -> Field<bool>*{return new Field<bool>(false, name, true); }},
		{"bottom", [](const std::string& name) -> Field<bool>*{return new Field<bool>(false, name, true); }}
	});
}

ConeFactory::ConeFactory()
{
	initTokens();
}

ConeFactory::ConeFactory(const std::string& name) : AbstractFactory(name) {
	initTokens();
}

ConeFactory::~ConeFactory() {

}
