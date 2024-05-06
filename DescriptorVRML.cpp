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
	std::string lol = filePart;
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
	delete *(--result.end());
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
	std::pair<size_t, size_t> bodySize = {_bracketsIndexes.top().first, _bracketsIndexes.top().second};
	_bracketsIndexes.push(std::pair<size_t, size_t>(0, 0));
	
	bool isExtern = false;
	bool isCustom = false;
	std::string customFieldName;
	//std::smatch(*_it).position() < bodySize.first + bodySize.second

	do {
		std::smatch wordMatch = std::smatch(*_it);
		std::string lol = wordMatch.str();

		int dele1 = wordMatch.position();
		if (wordMatch.position() < _bracketsIndexes.top().first + _bracketsIndexes.top().second) {
			if (_it != _end) {
				++_it;
			}
			continue;
		}
		_bracketsIndexes.top().first = 0;
		_bracketsIndexes.top().second = 0;

		if (wordMatch.str() == "extern") {
			isExtern = true;
			if (_it != _end) {
				++_it;
			}
			continue;
		}

		if (wordMatch.str() == "DEF") {
			customFieldName = std::smatch(*++_it).str() + " ";
			isCustom = true;
			if (_it != _end) {
				++_it;
			}
			continue;
		}

		if (wordMatch.str() == "USE") {
			customFieldName = std::smatch(*++_it).str() + " ";
			std::cout << "using " << customFieldName << std::endl;
			fieldToPut->addFieldPtr(_customFields.find(customFieldName)->second->copy());
			isCustom = false;
			customFieldName = "";
			if (_it != _end) {
				++_it;
			}
			continue;
		}

		auto token = fieldTokens.find(wordMatch.str());
		if (token == fieldTokens.end()) {
			std::cout << "token not found" << std::endl;
			if (_it != _end) {
				++_it;
			}
			continue;
		}
		

		std::smatch nextMatch = std::smatch(*(++_it));
		lol = nextMatch.str();
		size_t first = nextMatch.position() - bodySize.first;
		int sdsd = fileData.find("{");
		size_t second;

		if (nextMatch.str() == "USE") {
			customFieldName = std::smatch(*++_it).str() + " ";
			std::cout << "using " << customFieldName << std::endl;
			GroupField* singleField = new GroupField(isExtern, token->first);
			singleField->addFieldPtr(_customFields.find(customFieldName)->second->copy());
			fieldToPut->addFieldPtr(singleField);
			isCustom = false;
			customFieldName = "";
			if (_it != _end) {
				++_it;
			}
			continue;
		}

		if (nextMatch.str() == "{" || nextMatch.str() == "[") {
			second = findBodyLength(fileData.substr(first, fileData.size() - first));
			lol = fileData.substr(first, second);
			_bracketsIndexes.top().first = nextMatch.position();
			_bracketsIndexes.top().second = second;
			std::cout << "making " << customFieldName + token->first << std::endl;
			auto node = token->second(isExtern, customFieldName + token->first, fileData.substr(first, second));
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
			second = fileData.substr(first, fileData.size() - first).find("\n");
			_bracketsIndexes.top().first = nextMatch.position();
			_bracketsIndexes.top().second = second;
			auto node = token->second(isExtern, customFieldName + token->first, fileData.substr(first, second));
			fieldToPut->addFieldPtr(node);
			if (isCustom) {
				_customFields.insert({ customFieldName, node->copy()});
			}
			std::cout << "making " << customFieldName + token->first<< std::endl;

		}
		else {
			if (nextMatch.str() == "DEF") {
				isCustom = true;
				customFieldName = std::smatch(*(++_it)).str() + " ";
				nextMatch = std::smatch(*(++_it));
				first = nextMatch.position() - bodySize.first;
				nextToken = fieldTokens.find(nextMatch.str());
			}
			if (nextToken != fieldTokens.end()) {
				std::smatch singleFieldMatch = std::smatch(*(++_it));
				lol = singleFieldMatch.str();
				second = findBodyLength(fileData.substr(singleFieldMatch.position() - bodySize.first, bodySize.second)) + (singleFieldMatch.position() - nextMatch.position());
				_bracketsIndexes.top().first = nextMatch.position();
				_bracketsIndexes.top().second = second;
				lol = fileData.substr(first, second);
				GroupField* singleField = new GroupField(isExtern, token->first);
				auto node = nextToken->second(isExtern, customFieldName + nextToken->first, fileData.substr(first, second));
				singleField->addFieldPtr(node);
				fieldToPut->addFieldPtr(singleField);
				if (isCustom) {
					_customFields.insert({customFieldName,  node->copy()});
					isCustom = false;
					customFieldName = "";
				}
			}
		}
		isExtern = false;

	} while (_it != _end && std::smatch(*_it).position() < bodySize.first + bodySize.second);
	_bracketsIndexes.pop();
}

void DescriptorVRML::setWordsBegin(std::sregex_iterator begin, const std::string& file)
{
	_it = begin;
	_bracketsIndexes.push(std::pair<size_t, size_t>(0, file.size()));
}

DescriptorVRML::DescriptorVRML()
{
	_customFields = {};
	_it = std::sregex_iterator();
	_end = std::sregex_iterator();
	_bracketsIndexes = {};
}

DescriptorVRML::~DescriptorVRML()
{
	for (std::map<std::string, AbstractField*>::iterator it = _customFields.begin(); it != _customFields.end(); it++) {
		delete it->second;
	}
	_customFields.clear();
}