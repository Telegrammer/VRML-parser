#include "DescriptorVRML.h"

#include <iostream>
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

std::vector<float*> DescriptorVRML::parseStringIntoFloatVec(const std::string& filePart)
{
    std::vector<float*> result;
	std::vector<std::string> floatStrings;
    std::regex floatRegex = std::regex("(-?\\b\\d+\\.\\d+\\b|-?\\b\\d+\\b|-?\\.\\b\\d+\\b)");
    std::sregex_iterator floatsBegin = std::sregex_iterator(filePart.begin(), filePart.end(), floatRegex);
	std::transform(floatsBegin, std::sregex_iterator(), std::back_inserter(floatStrings), [](std::match_results<std::string::const_iterator> num) -> std::string {
		std::string str = num.str();
		if (str[0] == '.') {
			str.insert(0, "0");
		}
		return str;
	});
    std::transform(floatStrings.begin(), floatStrings.end(), std::back_inserter(result), [](std::string& num) -> float* {return new float(std::stof(num)); });
    return result;
}

float& DescriptorVRML::parseStringIntoFloat(const std::string& stringOfFloat) const
{
	float result = std::stof(stringOfFloat);
	if (stringOfFloat[0] == '.') {
		result = std::stof("0" + stringOfFloat);
	}
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
		std::smatch wordMatch = std::smatch(*it);;
		std::string lol = wordMatch.str();

		if (wordMatch.position() > bodySize.first && wordMatch.position() < bodySize.first + bodySize.second) {
			std::cout << lol << " " << "already initialized" << std::endl;
			continue;
		}

		if (wordMatch.str() == "extern") {
			isExtern = true;
			continue;
		}

		if (wordMatch.str() == "DEF") {
			customFieldName = std::smatch(*++it).str();
			isCustom = true;
			continue;
		}

		if (wordMatch.str() == "USE") {
			customFieldName = std::smatch(*++it).str();
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
			customFieldName = std::smatch(*++it).str();
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
			fieldToPut->addFieldPtr(token->second(isExtern, customFieldName + " " + token->first, fileData.substr(bodySize.first, bodySize.second)));
			if (isCustom) {
				_customFields.insert({ customFieldName, token->second(isExtern, customFieldName, fileData.substr(bodySize.first, bodySize.second))});
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
				customFieldName = std::smatch(*(++it)).str();
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
				singleField->addFieldPtr(nextToken->second(isExtern, customFieldName + " " + nextToken->first, fileData.substr(bodySize.first, bodySize.second)));
				fieldToPut->addFieldPtr(singleField);
				if (isCustom) {
					_customFields.insert({customFieldName,  nextToken->second(isExtern, customFieldName, fileData.substr(bodySize.first, bodySize.second)) });
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