#include "GroupFactory.h"

void GroupFactory::initTokens()
{
	_fieldTokens.insert({
						  {"bboxCenter",  [&](bool isExtern, const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(isExtern, name, _descriptor->parseStringIntoFloatVec(filePart)); }},
						  {"bboxSize",    [&](bool isExtern, const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(isExtern, name, _descriptor->parseStringIntoFloatVec(filePart)); }},
						  {"children",	  [](bool isExtern, const std::string& name, const std::string& filePart)->GroupField* {return ChildrenFactory(name).decrypt(isExtern, filePart); } },
						  {"Shape",		  [](bool isExtern, const std::string& name, const std::string& filePart)->GroupField* {return ShapeFactory(name).decrypt(isExtern, filePart); }} 
		});
	_fieldDefaultTokens.insert({
		{"bboxCenter",		 [](const std::string& name) -> Field<std::vector<float*>>*{ return new Field<std::vector<float*>>(false, name, {new float(0.0f), new float(0.0f), new float(0.0f)}); }},
		{"bboxSize",		 [](const std::string& name) -> Field<std::vector<float*>>*{ return new Field<std::vector<float*>>(false, name, {new float(-1.0f), new float(-1.0f), new float(-1.0f)}); }},
		{"children",		 [](const std::string& name) -> GroupField* {return new GroupField(false, name); } }
	});
}

GroupFactory::GroupFactory()
{
	initTokens();
}

GroupFactory::GroupFactory(const std::string& name) : AbstractFactory(name)
{
	initTokens();
}

GroupFactory::~GroupFactory()
{
}
