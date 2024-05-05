#include "WorldInfoFactory.h"

void WorldInfoFactory::initTokens() {
	_fieldTokens.insert({ {"info",	[&](bool isExtern, const std::string& name, const std::string& filePart) -> Field<std::vector<std::string*>>*{return new Field<std::vector<std::string*>>(isExtern, name, _descriptor->parseStringIntoStringVec(filePart)); }},
						  {"title", [](bool isExtern, const std::string& name, const std::string& filePart) -> Field<std::string>*{return new Field<std::string>(isExtern, name, "\"" + filePart); }}
	});
	_fieldDefaultTokens.insert({
		{"info",	[](const std::string& name) -> Field<std::vector<std::string*>>*{return new Field<std::vector<std::string*>>(false, name, {}); }},
		{"title",	[](const std::string& name) -> Field<std::string>*{return new Field<std::string>(false, name, "\"\""); }}
	});
}

WorldInfoFactory::WorldInfoFactory() {
	initTokens();
}

WorldInfoFactory::WorldInfoFactory(const std::string& name) : AbstractFactory(name) {
	initTokens();
}

WorldInfoFactory::~WorldInfoFactory() {
}
