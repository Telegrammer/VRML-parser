#pragma once


#include "GroupField.h"
#include <streambuf>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <stack>
#include <map>
#include <functional>

typedef std::map<std::string, std::function<AbstractField* (const std::string& name, const std::string& filePart)>> tokensIdentifier;
class DescriptorVRML {
public:
	DescriptorVRML();
	~DescriptorVRML();
	std::string readFile(const std::string& fileName);
	int findBodyLength(const std::string& filePart);
	std::vector<float*> parseStringIntoFloatVec(const std::string& stringOfFloats);
	void decrypt(const std::string& fileData, GroupField* fieldToPut, const tokensIdentifier& fieldTokens);
};