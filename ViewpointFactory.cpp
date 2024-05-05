#include "ViewpointFactory.h"

void ViewpointFactory::initTokens()
{
	_fieldTokens.insert({ {"fieldOfView",[&](bool isExtern, const std::string& name, const std::string& filePart) -> Field<float>*{return new Field<float>(isExtern, name, _descriptor->parseStringIntoFloat(filePart)); }},
						  {"position", [&](bool isExtern, const std::string& name, const std::string& filePart) -> Field<std::vector<float*>>*{return new Field<std::vector<float*>>(isExtern, name, _descriptor->parseStringIntoFloatVec(filePart)); }},
						  {"orientation", [&](bool isExtern, const std::string& name, const std::string& filePart) -> Field<std::vector<float*>>*{return new Field<std::vector<float*>>(isExtern, name, _descriptor->parseStringIntoFloatVec(filePart)); }},
						  {"jump", [&](bool isExtern, const std::string& name, const std::string& filePart) -> Field<bool>*{return new Field<bool>(isExtern, name, _descriptor->parseStringIntoBool(filePart)); }},
						  {"description", [](bool isExtern, const std::string& name, const std::string& filePart) -> Field<std::string>*{return new Field<std::string>(isExtern, name, '"' + filePart); }}
		});
	_fieldDefaultTokens.insert({
		{"fieldOfView", [](const std::string& name) -> Field<float>*{return new Field<float>(false, name, 0.785398f); }},
		{"position",	[](const std::string& name) -> Field<std::vector<float*>>*{return new Field<std::vector<float*>>(false, name, {new float(0.0f), new float(0.0f), new float(10.0f)}); }},
		{"orientation",	[](const std::string& name) -> Field<std::vector<float*>>*{return new Field<std::vector<float*>>(false, name, {new float(0.0f), new float(0.0f), new float(1.0f), new float(1.0f)}); }},
		{"description",	[](const std::string& name) -> Field<std::string>*{return new Field<std::string>(false, name, "\"\""); }},
		{"jump",		[](const std::string& name) -> Field<bool>*{return new Field<bool>(false, name, true); }},

	});
}

ViewpointFactory::ViewpointFactory()
{
	initTokens();
}

ViewpointFactory::ViewpointFactory(const std::string& name) : AbstractFactory(name)
{
	initTokens();
}

ViewpointFactory::~ViewpointFactory()
{
}
