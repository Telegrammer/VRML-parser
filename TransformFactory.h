#pragma once


#include "ChildrenFactory.h"
#include "ShapeFactory.h"

class TransformFactory : public AbstractFactory {
private:
	virtual void initTokens();
	TransformFactory(const TransformFactory& rhs) = delete;
	TransformFactory& operator=(const TransformFactory& rhs) = delete;
public:
	TransformFactory();
	TransformFactory(const std::string& name);
	virtual ~TransformFactory();
};