#include "TransformFactory.h"


void TransformFactory::initTokens()
{
	_fieldTokens = { {"translation", [](const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(false, name, _descriptor.parseStringIntoFloatVec(filePart)); }},
					 {"scale",		 [](const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(false, name, _descriptor.parseStringIntoFloatVec(filePart)); }},
					 {"scaleOrientation", [](const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(false, name, _descriptor.parseStringIntoFloatVec(filePart)); }},
					 {"center",		 [](const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(false, name, _descriptor.parseStringIntoFloatVec(filePart)); }},
					 {"rotation",    [](const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(false, name, _descriptor.parseStringIntoFloatVec(filePart)); }},
					 {"bboxCenter",  [](const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(false, name, _descriptor.parseStringIntoFloatVec(filePart)); }},
					 {"bboxSize", [](const std::string& name, const std::string& filePart)->Field<std::vector<float*>>*{return new Field<std::vector<float*>>(false, name, _descriptor.parseStringIntoFloatVec(filePart)); }},
					 {"children",	 [](const std::string& name, const std::string& filePart)->GroupField* {return ChildrenFactory(name).decrypt(filePart);} },
					 {"Shape",		 [](const std::string& name, const std::string& filePart)->GroupField* {return ShapeFactory(name).decrypt(filePart); }} };
	_fieldDefaultTokens = {
		{"scale",			 [](const std::string& name) -> Field<std::vector<float*>>*{ return new Field<std::vector<float*>>(false, name, {new float(0.0f), new float(0.0f), new float(0.0f)});}},
		{"scaleOrientation", [](const std::string& name) -> Field<std::vector<float*>>*{ return new Field<std::vector<float*>>(false, name, {new float(0.0f), new float(0.0f), new float(0.0f), new float(0.0f)}); }},
		{"center",			 [](const std::string& name) -> Field<std::vector<float*>>*{ return new Field<std::vector<float*>>(false, name, {new float(0.0f), new float(0.0f), new float(0.0f)}); }},
		{"translation",		 [](const std::string& name) -> Field<std::vector<float*>>*{ return new Field<std::vector<float*>>(false, name, {new float(0.0f), new float(0.0f), new float(0.0f)}); }},
		{"rotation",		 [](const std::string& name) -> Field<std::vector<float*>>*{ return new Field<std::vector<float*>>(false, name, {new float(0.0f), new float(0.0f), new float(0.0f)}); }},
		{"bboxCenter",		 [](const std::string& name) -> Field<std::vector<float*>>*{ return new Field<std::vector<float*>>(false, name, {new float(0.0f), new float(0.0f), new float(0.0f)}); }},
		{"bboxSize",		 [](const std::string& name) -> Field<std::vector<float*>>*{ return new Field<std::vector<float*>>(false, name, {new float(-1.0f), new float(-1.0f), new float(-1.0f)}); }},
		{"children",		 [](const std::string& name) -> GroupField* {return new GroupField(false, name); } }
	};
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
