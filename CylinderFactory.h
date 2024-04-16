#pragma once

#include "AbstractFactory.h"

class CylinderFactory : public AbstractFactory {
private:
	virtual void initTokens();
	CylinderFactory(const CylinderFactory& rhs) = delete;
	CylinderFactory& operator=(const CylinderFactory& rhs) = delete;
public:
	CylinderFactory();
	CylinderFactory(const std::string& name);
	virtual ~CylinderFactory();
};
