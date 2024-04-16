#pragma once

#include "AbstractFactory.h"

class BoxFactory : public AbstractFactory {
private:
	virtual void initTokens();
	BoxFactory(const BoxFactory& rhs) = delete;
	BoxFactory& operator=(const BoxFactory& rhs) = delete;
public:
	BoxFactory();
	BoxFactory(const std::string& name);
	virtual ~BoxFactory();
};
