#pragma once

#include "AbstractFactory.h"

class CoordinateFactory : public AbstractFactory {
private:
	virtual void initTokens();
	CoordinateFactory(const CoordinateFactory& rhs) = delete;
	CoordinateFactory& operator=(const CoordinateFactory& rhs) = delete;
public:
	CoordinateFactory();
	CoordinateFactory(const std::string& name);
	virtual ~CoordinateFactory();
};