#pragma once

#include "AbstractFactory.h"

class ConeFactory : public AbstractFactory {
private:
	virtual void initTokens();
	ConeFactory(const ConeFactory& rhs) = delete;
	ConeFactory& operator=(const ConeFactory& rhs) = delete;
public:
	ConeFactory();
	ConeFactory(const std::string& name);
	virtual ~ConeFactory();
};
