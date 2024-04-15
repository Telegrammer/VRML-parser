#include "MaterialFactory.h"

void MaterialFactory::initTokens()
{
	_fieldTokens = { { "diffuseColor", [](const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(false, name, _descriptor.parseStringIntoFloatVec(filePart)); } } };
	_fieldDefaultTokens = {
		{"diffuseColor", [](const std::string& name) -> Field<std::vector<float*>>*{return new Field<std::vector<float*>>(false, name, {new float(0.8f), new float(0.8f), new float(0.8f)}); }},
		{"ambientIntensity", [](const std::string& name) -> Field<float>*{return new Field<float>(false, name, 0.2f); }},
	    {"emissiveColor", [](const std::string& name) -> Field<std::vector<float*>>*{return new Field<std::vector<float*>>(false, name, {new float(0.0f), new float(0.0f), new float(0.0f)}); }},
		{"specularColor", [](const std::string& name) -> Field<std::vector<float*>>*{return new Field<std::vector<float*>>(false, name, {new float(0.0f), new float(0.0f), new float(0.0f)}); }},
		{"shinines", [](const std::string& name) -> Field<float>*{return new Field<float>(false, name, 0.2f); }},
		{"transparency", [](const std::string& name) -> Field<float>*{return new Field<float>(false, name, 0.2f); }}
	};
}

MaterialFactory::MaterialFactory() : AbstractFactory()
{
	initTokens();
}

MaterialFactory::MaterialFactory(const std::string& name) : AbstractFactory(name)
{
	initTokens();
}

MaterialFactory::~MaterialFactory()
{

}
