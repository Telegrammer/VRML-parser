#pragma once

#include "AbstractFactory.h"

class SphereFactory : public AbstractFactory {
private:
	virtual void initTokens();
	SphereFactory(const SphereFactory& rhs) = delete;
	SphereFactory& operator=(const SphereFactory& rhs) = delete;
public:
	SphereFactory();
	SphereFactory(const std::string& name);
	virtual ~SphereFactory();
};
