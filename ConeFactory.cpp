#include "ConeFactory.h"

void ConeFactory::initTokens()
{
	_fieldTokens = { {"radius", [](const std::string& name, const std::string& filePart)->Field<float>*{return new Field<float>(false, name, _descriptor.parseStringIntoFloat(filePart)); }},
					 {"height", [](const std::string& name, const std::string& filePart)->Field<float>*{return new Field<float>(false, name, _descriptor.parseStringIntoFloat(filePart)); }}};
	_fieldDefaultTokens = { {"side", [](const std::string& name) -> Field<bool>*{return new Field<bool>(false, name, true); }},
							{"bottom", [](const std::string& name) -> Field<bool>*{return new Field<bool>(false, name, true); }} };
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
