#include "BackgroundFactory.h"

void BackgroundFactory::initTokens()
{
	_fieldTokens.insert({ {"skyColor", [&](bool isExtern, const std::string& name, const std::string& filePart) -> Field<std::vector<float*>>*{return new Field<std::vector<float*>>(isExtern, name, _descriptor->parseStringIntoFloatVec(filePart)); }}
	});
	_fieldDefaultTokens.insert({
		{"skyColor",	[](const std::string& name) -> Field<std::vector<float*>>*{return new Field<std::vector<float*>>(false, name, {}); }},
	});
}

BackgroundFactory::BackgroundFactory()
{
	initTokens();
}

BackgroundFactory::BackgroundFactory(const std::string& name) : AbstractFactory(name)
{
	initTokens();
}

BackgroundFactory::~BackgroundFactory()
{
}
