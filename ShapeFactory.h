#pragma once


#include "AbstractFactory.h"

class ShapeFactory : public AbstractFactory {
private:
	virtual void initTokens();
	ShapeFactory(const ShapeFactory& rhs) = delete;
	ShapeFactory& operator=(const ShapeFactory& rhs) = delete;
public:
	ShapeFactory();
	ShapeFactory(const std::string& name);
	virtual ~ShapeFactory();
};