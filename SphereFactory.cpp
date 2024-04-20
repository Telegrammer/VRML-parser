#include "SphereFactory.h"

void SphereFactory::initTokens()
{
	_fieldTokens.insert({ {"radius", [](const std::string& name, const std::string& filePart) -> Field<float>*{ return new Field<float>(false, name, _descriptor.parseStringIntoFloat(filePart)); }} });
	_fieldDefaultTokens.insert({ {"radius", [](const std::string& name) -> Field<float>*{ return new Field<float>(false, name, 1.0f); }} });
}

SphereFactory::SphereFactory()
{
	initTokens();
}

SphereFactory::SphereFactory(const std::string& name) : AbstractFactory(name)
{
	initTokens();
}

SphereFactory::~SphereFactory()
{

}

