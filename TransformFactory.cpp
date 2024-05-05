#include "TransformFactory.h"


void TransformFactory::initTokens()
{
	_fieldTokens.insert({ {"translation", [&](bool isExtern, const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(isExtern, name, _descriptor->parseStringIntoFloatVec(filePart)); }},
						  {"scale",		  [&](bool isExtern, const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(isExtern, name, _descriptor->parseStringIntoFloatVec(filePart)); }},
						  {"scaleOrientation", [&](bool isExtern, const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(isExtern, name, _descriptor->parseStringIntoFloatVec(filePart)); }},
						  {"center",	  [&](bool isExtern, const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(isExtern, name, _descriptor->parseStringIntoFloatVec(filePart)); }},
						  {"rotation",    [&](bool isExtern, const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(isExtern, name, _descriptor->parseStringIntoFloatVec(filePart)); }},
						  {"bboxCenter",  [&](bool isExtern, const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(isExtern, name, _descriptor->parseStringIntoFloatVec(filePart)); }},
						  {"bboxSize",    [&](bool isExtern, const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(isExtern, name, _descriptor->parseStringIntoFloatVec(filePart)); }},
						  {"children",	  [](bool isExtern, const std::string& name, const std::string& filePart)->GroupField* {return ChildrenFactory(name).decrypt(isExtern, filePart); } },
						  {"Shape",		  [](bool isExtern, const std::string& name, const std::string& filePart)->GroupField* {return ShapeFactory(name).decrypt(isExtern, filePart); }}
						 });
	_fieldDefaultTokens.insert({
		{"scale",			 [](const std::string& name) -> Field<std::vector<float*>>*{ return new Field<std::vector<float*>>(false, name, {new float(0.0f), new float(0.0f), new float(0.0f)});}},
		{"scaleOrientation", [](const std::string& name) -> Field<std::vector<float*>>*{ return new Field<std::vector<float*>>(false, name, {new float(0.0f), new float(0.0f), new float(0.0f), new float(0.0f)}); }},
		{"center",			 [](const std::string& name) -> Field<std::vector<float*>>*{ return new Field<std::vector<float*>>(false, name, {new float(0.0f), new float(0.0f), new float(0.0f)}); }},
		{"translation",		 [](const std::string& name) -> Field<std::vector<float*>>*{ return new Field<std::vector<float*>>(false, name, {new float(0.0f), new float(0.0f), new float(0.0f)}); }},
		{"rotation",		 [](const std::string& name) -> Field<std::vector<float*>>*{ return new Field<std::vector<float*>>(false, name, {new float(0.0f), new float(0.0f), new float(0.0f)}); }},
		{"bboxCenter",		 [](const std::string& name) -> Field<std::vector<float*>>*{ return new Field<std::vector<float*>>(false, name, {new float(0.0f), new float(0.0f), new float(0.0f)}); }},
		{"bboxSize",		 [](const std::string& name) -> Field<std::vector<float*>>*{ return new Field<std::vector<float*>>(false, name, {new float(-1.0f), new float(-1.0f), new float(-1.0f)}); }},
		{"children",		 [](const std::string& name) -> GroupField* {return new GroupField(false, name); } }
	});
}

TransformFactory::TransformFactory() {
	initTokens();
}

TransformFactory::TransformFactory(const std::string& name) : AbstractFactory(name) {
	initTokens();
}

TransformFactory::~TransformFactory()
{
}
