#pragma once

#include "ShapeFactory.h"
#include "ChildrenFactory.h"

class GroupFactory : public AbstractFactory {
private:
	virtual void initTokens();
	GroupFactory(const GroupFactory& rhs) = delete;
	GroupFactory& operator=(const GroupFactory& rhs) = delete;
public:
	GroupFactory();
	GroupFactory(const std::string& name);
	virtual ~GroupFactory();
};