#include "DescriptorVRML.h"
#include <iostream>

DescriptorVRML* DescriptorVRML::_instance = nullptr;

DescriptorVRML* DescriptorVRML::getInstance()
{
	if (_instance == nullptr) {
		_instance = new DescriptorVRML();
	}
	return _instance;
}

void DescriptorVRML::deleteInstance()
{
	if (_instance != nullptr) {
		delete _instance;
	}
}

std::string DescriptorVRML::readFile(const std::string& fileName)
{
    return std::string(
        (std::istreambuf_iterator<char>(*(std::unique_ptr<std::ifstream>(new std::ifstream(fileName))).get())),
        std::istreambuf_iterator<char>());
}

int DescriptorVRML::findBodyLength(const std::string& filePart)
{
    int index = 0;
    std::stack<int> openedBrackets;
    do {
        switch (filePart[index])
        {
        case '{':
        case '[':
            openedBrackets.push(index);
            break;
        case '}':
        case ']':
            openedBrackets.pop();
            break;
        default:
            break;
        }
        ++index;
    } while (!openedBrackets.empty());
    return index;
}

std::vector<int*> DescriptorVRML::parseStringIntoIntVec(const std::string& filePart) {
	std::vector<int*> result;
	result.reserve(VECTOR_RESERVE_SIZE);
	std::regex intRegex = std::regex("-?\\b\\d+\\b");
	std::sregex_iterator intsBegin = std::sregex_iterator(filePart.begin(), filePart.end(), intRegex);
	std::transform(intsBegin, std::sregex_iterator(), std::back_inserter(result), [](std::match_results<std::string::const_iterator> num) -> int* {return new int(std::stoi(num.str())); });
	return result;
}

std::vector<std::string*> DescriptorVRML::parseStringIntoStringVec(const std::string& filePart) {
	std::vector<std::string*> result;
	result.reserve(VECTOR_RESERVE_SIZE);
	std::regex stringRegex = std::regex("\".*\"");
	std::sregex_iterator stringsBegin = std::sregex_iterator(filePart.begin(), filePart.end(), stringRegex);
	std::transform(stringsBegin, std::sregex_iterator(), std::back_inserter(result), [](std::match_results<std::string::const_iterator> str) -> std::string* {return new std::string(str.str()); });
	return result;
}

std::vector<float*> DescriptorVRML::parseStringIntoFloatVec(const std::string& filePart)
{
    std::vector<float*> result;
	result.reserve(VECTOR_RESERVE_SIZE);
    std::regex floatRegex = std::regex("(-?\\b\\d+\\.\\d+E?-?\\d*\\b|-?\\b\\d+\\b|-?\\.\\b\\d+E?-?\\d*\\b)");
    std::sregex_iterator floatsBegin = std::sregex_iterator(filePart.begin(), filePart.end(), floatRegex);
	std::transform(floatsBegin, std::sregex_iterator(), std::back_inserter(result), [](std::match_results<std::string::const_iterator> num)->float* {return new float(std::stof(num.str())); });
    return result;
}

std::vector<Vector3f*> DescriptorVRML::parseStringIntoVector3f(const std::string& filePart)
{
	std::vector<Vector3f*> result;
	result.reserve(VECTOR_RESERVE_SIZE);
	std::regex vector3fRegex = std::regex(".*[^,]");
	std::sregex_iterator vector3fBegin = std::sregex_iterator(filePart.begin(), filePart.end(), vector3fRegex);
	std::transform(vector3fBegin, std::sregex_iterator(), std::back_inserter(result), [&](std::match_results<std::string::const_iterator> vec)->Vector3f* {return new Vector3f(parseStringIntoFloatVec(vec.str())); });
	delete* (--result.end());
	result.pop_back();
	return result;
}

float& DescriptorVRML::parseStringIntoFloat(const std::string& stringOfFloat) const
{
	float result = std::stof(stringOfFloat);

	return result;
}

bool DescriptorVRML::parseStringIntoBool(const std::string& stringOfBool) const
{
	return stringOfBool == "TRUE" ? true : false;
}

void DescriptorVRML::decrypt(const std::string& fileData, GroupField* fieldToPut, const tokensIdentifier& fieldTokens)
{
	std::pair<size_t, size_t> bodySize = { 0, 0 };
	std::regex wordsRegex("(\\b\\w+\\b|\\{|\\[)");
	std::sregex_iterator wordsBegin = std::sregex_iterator(fileData.begin(), fileData.end(), wordsRegex);
	std::sregex_iterator wordsEnd = std::sregex_iterator();

	bool isExtern = false;
	bool isCustom = false;
	std::string customFieldName;

	for (std::sregex_iterator it = wordsBegin; it != wordsEnd; it++) {
		std::smatch wordMatch = std::smatch(*it);
		std::string lol = wordMatch.str();

		if (wordMatch.position() > bodySize.first && wordMatch.position() < bodySize.first + bodySize.second) {
			continue;
		}

		if (wordMatch.str() == "extern") {
			isExtern = true;
			continue;
		}

		if (wordMatch.str() == "DEF") {
			customFieldName = std::smatch(*++it).str() + " ";
			isCustom = true;
			continue;
		}

		if (wordMatch.str() == "USE") {
			customFieldName = std::smatch(*++it).str() + " ";
			std::cout << "using " << customFieldName << std::endl;
			fieldToPut->addFieldPtr(_customFields.find(customFieldName)->second->copy());
			isCustom = false;
			customFieldName = "";
			continue;
		}

		auto token = fieldTokens.find(wordMatch.str());
		if (token == fieldTokens.end()) {
			std::cout << "token not found" << std::endl;
			continue;
		}
		

		std::smatch nextMatch = std::smatch(*(++it));
		lol = nextMatch.str();
		bodySize.first = nextMatch.position();

		if (nextMatch.str() == "USE") {
			customFieldName = std::smatch(*++it).str() + " ";
			std::cout << "using " << customFieldName << std::endl;
			GroupField* singleField = new GroupField(isExtern, token->first);
			singleField->addFieldPtr(_customFields.find(customFieldName)->second->copy());
			fieldToPut->addFieldPtr(singleField);
			isCustom = false;
			customFieldName = "";
			continue;
		}

		if (nextMatch.str() == "{" || nextMatch.str() == "[") {
			bodySize.second = findBodyLength(fileData.substr(bodySize.first, fileData.size() - bodySize.first));
			std::cout << "making " << customFieldName + token->first << std::endl;
			auto node = token->second(isExtern, customFieldName + token->first, fileData.substr(bodySize.first, bodySize.second));
			fieldToPut->addFieldPtr(node);
			if (isCustom) {
				_customFields.insert({ customFieldName, node->copy()});
				isCustom = false;
				customFieldName = "";
			}
			isExtern = false;
			continue;
		}

		auto nextToken = fieldTokens.find(nextMatch.str());

		if (nextToken == fieldTokens.end() && nextMatch.str() != "DEF") {
			bodySize.second = fileData.substr(bodySize.first, fileData.size() - bodySize.first).find("\n");
			fieldToPut->addFieldPtr(token->second(isExtern, customFieldName + token->first, fileData.substr(bodySize.first, bodySize.second)));
			if (isCustom) {
				_customFields.insert({ customFieldName, token->second(isExtern, customFieldName, fileData.substr(bodySize.first, bodySize.second)) });
			}
			std::cout << "making " << customFieldName + token->first<< std::endl;
		}
		else {
			if (nextMatch.str() == "DEF") {
				isCustom = true;
				customFieldName = std::smatch(*(++it)).str() + " ";
				nextMatch = std::smatch(*(++it));
				bodySize.first = nextMatch.position();
				nextToken = fieldTokens.find(nextMatch.str());
			}
			if (nextToken != fieldTokens.end()) {
				std::smatch singleFieldMatch = std::smatch(*(++it));
				lol = singleFieldMatch.str();
				bodySize.second = findBodyLength(fileData.substr(singleFieldMatch.position(), fileData.size() - singleFieldMatch.position())) + (singleFieldMatch.position() - nextMatch.position());
				lol = fileData.substr(bodySize.first, bodySize.second);
				GroupField* singleField = new GroupField(isExtern, token->first);
				singleField->addFieldPtr(nextToken->second(isExtern, customFieldName + nextToken->first, fileData.substr(bodySize.first, bodySize.second)));
				fieldToPut->addFieldPtr(singleField);
				if (isCustom) {
					_customFields.insert({customFieldName,  nextToken->second(isExtern, customFieldName + nextToken->first, fileData.substr(bodySize.first, bodySize.second))});
					isCustom = false;
					customFieldName = "";
				}
			}
		}
		isExtern = false;
	}
}

DescriptorVRML::DescriptorVRML()
{
	_customFields = {};
}

DescriptorVRML::~DescriptorVRML()
{
	for (std::map<std::string, AbstractField*>::iterator it = _customFields.begin(); it != _customFields.end(); it++) {
		delete it->second;
	}
	_customFields.clear();
}