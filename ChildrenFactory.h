#pragma once

#include "ShapeFactory.h"


class ChildrenFactory : public AbstractFactory {
private:
	virtual void initTokens();
	ChildrenFactory(const ChildrenFactory& rhs) = delete;
	ChildrenFactory& operator=(const ChildrenFactory& rhs) = delete;
public:
	ChildrenFactory();
	ChildrenFactory(const std::string& name);
	virtual ~ChildrenFactory();
};