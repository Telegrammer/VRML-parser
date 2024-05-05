#include "IndexedLineSetFactory.h"

void IndexedLineSetFactory::initTokens()
{
	_fieldTokens.insert({ {"coord",		 [](bool isExtern, const std::string& name, const std::string& filePart) -> GroupField* {return new GroupField(isExtern, name); }},
						  {"Coordinate", [](bool isExtern, const std::string& name, const std::string& filePart) -> GroupField* {return CoordinateFactory(name).decrypt(isExtern, filePart); }},
						  {"coordIndex", [&](bool isExtern, const std::string& name, const std::string& filePart) -> Field<std::vector<int*>>*{return new Field<std::vector<int*>>(isExtern, name, _descriptor->parseStringIntoIntVec(filePart)); }}
	});
	_fieldDefaultTokens.insert({ 
		{"coord",		 [](const std::string& name) -> GroupField* {return new GroupField(false, name); }},
		{"coordIndex",   [](const std::string& name) -> Field<std::vector<int*>>*{return new Field<std::vector<int*>>(false, name, {}); }}
	});
}

IndexedLineSetFactory::IndexedLineSetFactory()
{
	initTokens();
}

IndexedLineSetFactory::IndexedLineSetFactory(const std::string& name) : AbstractFactory(name)
{
	initTokens();
}

IndexedLineSetFactory::~IndexedLineSetFactory()
{
}
