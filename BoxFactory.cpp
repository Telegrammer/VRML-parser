#include "BoxFactory.h"

void BoxFactory::initTokens()
{
	_fieldTokens.insert({ { "size", [](bool isExtern, const std::string& name, const std::string& filePart) -> Field<std::vector<float*>>*{ return new Field<std::vector<float*>>(isExtern, name, _descriptor.parseStringIntoFloatVec(filePart)); }} });
	_fieldDefaultTokens.insert({ { "size", [](const std::string& name) -> Field<std::vector<float*>>*{ return new Field<std::vector<float*>>(false, name, {new float(2.0f), new float(2.0f), new float(2.0f)}); }}});
}

BoxFactory::BoxFactory()
{
	initTokens();
}

BoxFactory::BoxFactory(const std::string& name) : AbstractFactory(name)
{
	initTokens();
}

BoxFactory::~BoxFactory() {

}