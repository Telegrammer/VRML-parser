#pragma once

#include "AbstractFactory.h"

class BackgroundFactory : public AbstractFactory {
private:
	virtual void initTokens();
	BackgroundFactory(const BackgroundFactory& rhs) = delete;
	BackgroundFactory& operator=(const BackgroundFactory& rhs) = delete;
public:
	BackgroundFactory();
	BackgroundFactory(const std::string& name);
	virtual ~BackgroundFactory();
};