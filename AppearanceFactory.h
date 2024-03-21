#pragma once


#include "AbstractFactory.h"

class AppearanceFactory : public AbstractFactory {
private:
	virtual void initTokens();
	AppearanceFactory(const AppearanceFactory& rhs) = delete;
	AppearanceFactory& operator=(const AppearanceFactory& rhs) = delete;
public:
	AppearanceFactory();
	AppearanceFactory(const std::string& name);
	virtual ~AppearanceFactory();
};