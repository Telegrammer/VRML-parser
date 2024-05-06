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

typedef std::map<std::string, std::function<AbstractField* (bool isExtern, const std::string& name, const std::string& filePart)>> tokensIdentifier;

class DescriptorVRML {
private:
	static DescriptorVRML* _instance;
	std::stack<std::pair<size_t, size_t>> _bracketsIndexes;
	std::sregex_iterator _it;
	std::sregex_iterator _end;
	DescriptorVRML();
	~DescriptorVRML();
	DescriptorVRML(const DescriptorVRML& rhs) = delete;
	DescriptorVRML& operator=(const DescriptorVRML& rhs) = delete;
	std::map<std::string, AbstractField*> _customFields;
public:
	static DescriptorVRML* getInstance();
	static void deleteInstance();
	void setWordsBegin(std::sregex_iterator begin, const std::string& file);
	std::string readFile(const std::string& fileName);
	int findBodyLength(const std::string& filePart);

	std::vector<std::string*> parseStringIntoStringVec(const std::string& rawString);
	std::vector<int*> parseStringIntoIntVec(const std::string& stringOfInts);
	std::vector<float*> parseStringIntoFloatVec(const std::string& stringOfFloats);
	std::vector<Vector3f*> parseStringIntoVector3f(const std::string& stringOfFloats);
	float& parseStringIntoFloat(const std::string& stringOfFloat) const;
	bool parseStringIntoBool(const std::string& stringOfBool) const;
	
	void decrypt(const std::string& fileData, GroupField* fieldToPut, const tokensIdentifier& fieldTokens);
};
