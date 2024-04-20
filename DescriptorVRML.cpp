#include "DescriptorVRML.h"

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
		auto token = fieldTokens.find(wordMatch.str());

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
			fieldToPut->addFieldPtr(_customFields.find(customFieldName)->second->copy());
			isCustom = false;
			customFieldName = "";
			continue;
		}
		if (token == fieldTokens.end()) {
			continue;
		}
		if (wordMatch.position() > bodySize.first && wordMatch.position() < bodySize.second) {
			continue;
		}
		

		std::smatch nextMatch = std::smatch(*(++it));
		lol = nextMatch.str();
		bodySize.first = nextMatch.position();

		if (nextMatch.str() == "{" || nextMatch.str() == "[") {
			bodySize.second = findBodyLength(fileData.substr(bodySize.first, fileData.size() - bodySize.first));
			fieldToPut->addFieldPtr(token->second(isExtern, customFieldName + token->first, fileData.substr(bodySize.first, bodySize.second)));
			if (isCustom) {
				_customFields.insert({ customFieldName, token->second(isExtern, customFieldName, fileData.substr(bodySize.first, bodySize.second)) });
				isCustom = false;
				customFieldName = "";
			}
			isExtern = false;
			continue;
		}

		auto nextToken = fieldTokens.find(nextMatch.str());
		if (nextToken == fieldTokens.end()) {
			bodySize.second = fileData.substr(bodySize.first, fileData.size() - bodySize.first).find("\n");
			fieldToPut->addFieldPtr(token->second(isExtern, customFieldName + token->first, fileData.substr(bodySize.first, bodySize.second)));
			if (isCustom) {
				_customFields.insert({ customFieldName, token->second(isExtern, customFieldName, fileData.substr(bodySize.first, bodySize.second)) });
			}
		}
		else {
			std::smatch singleFieldMatch = std::smatch(*(++it));
			bodySize.second = findBodyLength(fileData.substr(singleFieldMatch.position(), fileData.size() - singleFieldMatch.position())) + (singleFieldMatch.position() - nextMatch.position());
			GroupField* singleField = new GroupField(isExtern, customFieldName + token->first);
			singleField->addFieldPtr(nextToken->second(isExtern, nextToken->first, fileData.substr(bodySize.first, bodySize.second)));
			fieldToPut->addFieldPtr(singleField);
			if (isCustom) {
				singleField = new GroupField(isExtern, customFieldName);
				singleField->addFieldPtr(nextToken->second(isExtern, nextToken->first, fileData.substr(bodySize.first, bodySize.second)));
				_customFields.insert({ customFieldName, singleField });
			}
		}
		isExtern = false;
		isCustom = false;
		customFieldName = "";
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