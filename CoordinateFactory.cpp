#include "CoordinateFactory.h"

void CoordinateFactory::initTokens()
{
	_fieldTokens.insert({ {"point", [&](bool isExtern, const std::string& name, const std::string& filePart) -> Field<std::vector<float*>>*{ return new Field<std::vector<float*>>(isExtern, name, _descriptor->parseStringIntoFloatVec(filePart)); }} });
}

CoordinateFactory::CoordinateFactory()
{
	initTokens();
}

CoordinateFactory::CoordinateFactory(const std::string& name) : AbstractFactory(name)
{
	initTokens();
}

CoordinateFactory::~CoordinateFactory()
{
}
