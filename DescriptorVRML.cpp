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
    std::regex floatRegex = std::regex("(-?\\b\\d+\\.\\d+\\b|-?\\b\\d+\\b)");
    std::sregex_iterator floatsBegin = std::sregex_iterator(filePart.begin(), filePart.end(), floatRegex);
    std::transform(floatsBegin, std::sregex_iterator(), std::back_inserter(result), [](std::match_results<std::string::const_iterator> num) -> float* {return new float(std::stof(num.str())); });
    return result;
}

float& DescriptorVRML::parseStringIntoFloat(const std::string& stringOfFloat) const
{
	float result = std::stof(stringOfFloat);
	return result;
}

void DescriptorVRML::decrypt(const std::string& fileData, GroupField* fieldToPut, const tokensIdentifier& fieldTokens)
{
	std::pair<size_t, size_t> bodySize = { 0, 0 };
	std::regex wordsRegex("(\\b\\w+\\b|\\{|\\[)");
	std::sregex_iterator wordsBegin = std::sregex_iterator(fileData.begin(), fileData.end(), wordsRegex);
	std::sregex_iterator wordsEnd = std::sregex_iterator();

	for (std::sregex_iterator it = wordsBegin; it != wordsEnd; it++) {
		std::smatch wordMatch = std::smatch(*it);
		std::string lol = wordMatch.str();
		auto token = fieldTokens.find(wordMatch.str());

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
			fieldToPut->addFieldPtr(token->second(token->first, fileData.substr(bodySize.first, bodySize.second)));
			continue;
		}

		auto nextToken = fieldTokens.find(nextMatch.str());
		if (nextToken == fieldTokens.end()) {
			bodySize.second = fileData.substr(bodySize.first, fileData.size() - bodySize.first).find("\n");
		}
		else {
			std::smatch singleFieldMatch = std::smatch(*(++it));
			bodySize.second = findBodyLength(fileData.substr(singleFieldMatch.position(), fileData.size() - singleFieldMatch.position())) + (singleFieldMatch.position() - nextMatch.position());
		}
		fieldToPut->addFieldPtr(token->second(token->first, fileData.substr(bodySize.first, bodySize.second)));

	}
}


DescriptorVRML::DescriptorVRML()
{
}

DescriptorVRML::~DescriptorVRML()
{
}