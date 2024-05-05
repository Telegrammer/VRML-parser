#include "IndexedFaceSetFactory.h"

void IndexedFaceSetFactory::initTokens()
{
	_fieldTokens.insert({ {"solid",		  [&](bool isExtern, const std::string& name, const std::string& filePart) -> Field<bool>*{return new Field<bool>(isExtern, name, _descriptor->parseStringIntoBool(filePart)); }},
						  {"convex",	  [&](bool isExtern, const std::string& name, const std::string& filePart) -> Field<bool>*{return new Field<bool>(isExtern, name, _descriptor->parseStringIntoBool(filePart)); }},
						  {"ccw",		  [&](bool isExtern, const std::string& name, const std::string& filePart) -> Field<bool>*{return new Field<bool>(isExtern, name, _descriptor->parseStringIntoBool(filePart)); }},
						  {"normalIndex", [&](bool isExtern, const std::string& name, const std::string& filePart) -> Field<std::vector<int*>>*{return new Field<std::vector<int*>>(isExtern, name, _descriptor->parseStringIntoIntVec(filePart)); }},
						  {"normal", [](bool isExtern, const std::string& name, const std::string& filePart) -> GroupField* {return new GroupField(isExtern, name); }},
						  {"Normal", [](bool isExtern, const std::string& name, const std::string& filePart) -> GroupField* {return NormalFactory(name).decrypt(isExtern, filePart); }}
	});
	_fieldDefaultTokens.insert({
		{"solid",  [](const std::string& name) -> Field<bool>*{return new Field<bool>(false, name, true); }},
		{"convex", [](const std::string& name) -> Field<bool>*{return new Field<bool>(false, name, true); }},
		{"ccw",    [](const std::string& name) -> Field<bool>*{return new Field<bool>(false, name, true); }},
		{"normalIndex", [](const std::string& name) ->Field<std::vector<int*>>*{return new Field<std::vector<int*>>(false, name, {}); }},
		{"normal", [](const std::string& name) -> GroupField* {return new GroupField(false, name); }}
	});
}

IndexedFaceSetFactory::IndexedFaceSetFactory()
{
	initTokens();
}

IndexedFaceSetFactory::IndexedFaceSetFactory(const std::string& name) : IndexedLineSetFactory(name)
{
	initTokens();
}

IndexedFaceSetFactory::~IndexedFaceSetFactory()
{
}
