#include "NormalFactory.h"

void NormalFactory::initTokens()
{
	_fieldTokens.insert({{"vector", [&](bool isExtern, const std::string& name, const std::string& filePart) -> Field<std::vector<Vector3f*>>*{return new Field<std::vector<Vector3f*>>(isExtern, name, _descriptor->parseStringIntoVector3f(filePart)); }}
	});
	_fieldDefaultTokens.insert({
		{"vector",   [](const std::string& name) -> Field<std::vector<Vector3f*>>*{return new Field<std::vector<Vector3f*>>(false, name, {}); }}
	});
}

NormalFactory::NormalFactory()
{
	initTokens();
}

NormalFactory::NormalFactory(const std::string& name) : AbstractFactory(name)
{
	initTokens();
}

NormalFactory::~NormalFactory()
{
}
