#include "MaterialFactory.h"

void MaterialFactory::initTokens()
{
	_fieldTokens.insert({ { "diffuseColor",   [](bool isExtern, const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(isExtern, name, _descriptor.parseStringIntoFloatVec(filePart)); } },
						{ "emissiveColor",    [](bool isExtern, const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(isExtern, name, _descriptor.parseStringIntoFloatVec(filePart)); } },
						{ "specularColor",    [](bool isExtern, const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(isExtern, name, _descriptor.parseStringIntoFloatVec(filePart)); } },
						{ "ambientIntensity", [](bool isExtern, const std::string& name, const std::string& filePart)->Field<float>*{return new Field<float>(isExtern, name, _descriptor.parseStringIntoFloat(filePart)); } },
						{ "shinines",		  [](bool isExtern, const std::string& name, const std::string& filePart)->Field<float>*{return new Field<float>(isExtern, name, _descriptor.parseStringIntoFloat(filePart)); } },
						{ "transparency",     [](bool isExtern, const std::string& name, const std::string& filePart)->Field<float>*{return new Field<float>(isExtern, name, _descriptor.parseStringIntoFloat(filePart)); } } });
	
	
	
	
	_fieldDefaultTokens.insert({
		{"diffuseColor",	 [](const std::string& name) -> Field<std::vector<float*>>*{return new Field<std::vector<float*>>(false, name, {new float(0.8f), new float(0.8f), new float(0.8f)}); }},
		{"ambientIntensity", [](const std::string& name) -> Field<float>*{return new Field<float>(false, name, 0.2f); }},
	    {"emissiveColor",	 [](const std::string& name) -> Field<std::vector<float*>>*{return new Field<std::vector<float*>>(false, name, {new float(0.0f), new float(0.0f), new float(0.0f)}); }},
		{"specularColor",	 [](const std::string& name) -> Field<std::vector<float*>>*{return new Field<std::vector<float*>>(false, name, {new float(0.0f), new float(0.0f), new float(0.0f)}); }},
		{"shinines",		 [](const std::string& name) -> Field<float>*{return new Field<float>(false, name, 0.2f); }},
		{"transparency",	 [](const std::string& name) -> Field<float>*{return new Field<float>(false, name, 0.2f); }}
	});
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
