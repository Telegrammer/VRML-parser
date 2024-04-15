#include "GeometryFactory.h"

void GeometryFactory::initTokens() {
	_fieldTokens = { {"Cone", [](const std::string& name, const std::string& filePart)->GroupField* {return ConeFactory(name).decrypt(filePart); }} };
}
GeometryFactory::GeometryFactory()
{
	initTokens();
}

GeometryFactory::GeometryFactory(const std::string& name) : AbstractFactory(name)
{
	initTokens();
}


GeometryFactory::~GeometryFactory() {
}


