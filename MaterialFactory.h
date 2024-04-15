#pragma once


#include "AbstractFactory.h"

class MaterialFactory : public AbstractFactory {
private:
	virtual void initTokens();
	MaterialFactory(const MaterialFactory& rhs) = delete;
	MaterialFactory& operator=(const MaterialFactory& rhs) = delete;
public:
	MaterialFactory();
	MaterialFactory(const std::string& name);
	virtual ~MaterialFactory();
};
