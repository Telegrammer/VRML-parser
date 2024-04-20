#include "CylinderFactory.h"

void CylinderFactory::initTokens()
{
	_fieldTokens.insert({ {"radius", [](bool isExtern, const std::string& name, const std::string& filePart)->Field<float>*{return new Field<float>(isExtern, name, _descriptor.parseStringIntoFloat(filePart)); }},
						  {"height", [](bool isExtern, const std::string& name, const std::string& filePart)->Field<float>*{return new Field<float>(isExtern, name, _descriptor.parseStringIntoFloat(filePart)); }},
						  {"side",   [](bool isExtern, const std::string& name, const std::string& filePart)->Field<bool>*{return new Field<bool>(isExtern, name, _descriptor.parseStringIntoBool(filePart)); }},
						  {"bottom", [](bool isExtern, const std::string& name, const std::string& filePart)->Field<bool>*{return new Field<bool>(isExtern, name, _descriptor.parseStringIntoBool(filePart)); }},
						  {"top",    [](bool isExtern, const std::string& name, const std::string& filePart)->Field<bool>*{return new Field<bool>(isExtern, name, _descriptor.parseStringIntoBool(filePart)); }}
	});
	_fieldDefaultTokens.insert({
		{"radius", [](const std::string& name) -> Field<float>*{return new Field<float>(false, name, 1.0f); }},
		{"height", [](const std::string& name) -> Field<float>*{return new Field<float>(false, name, 2.0f); }},
		{"side",   [](const std::string& name) -> Field<bool>*{return new Field<bool>(false, name, true); }},
		{"bottom", [](const std::string& name) -> Field<bool>*{return new Field<bool>(false, name, true); }},
		{"top",    [](const std::string& name) -> Field<bool>*{return new Field<bool>(false, name, true); }}
	});
}

CylinderFactory::CylinderFactory()
{
	initTokens();
}

CylinderFactory::CylinderFactory(const std::string& name) : AbstractFactory(name)
{
	initTokens();
}

CylinderFactory::~CylinderFactory()
{
}
