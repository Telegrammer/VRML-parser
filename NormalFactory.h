#pragma once

#include "AbstractFactory.h"

class NormalFactory : public AbstractFactory {
private:
	virtual void initTokens();
	NormalFactory(const NormalFactory& rhs) = delete;
	NormalFactory& operator=(const NormalFactory& rhs) = delete;
public:
	NormalFactory();
	NormalFactory(const std::string& name);
	virtual ~NormalFactory();
};