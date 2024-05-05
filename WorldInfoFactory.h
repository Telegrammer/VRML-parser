#pragma once

#include "AbstractFactory.h"

class WorldInfoFactory : public AbstractFactory {
private:
	virtual void initTokens();
	WorldInfoFactory(const WorldInfoFactory& rhs) = delete;
	WorldInfoFactory& operator=(const WorldInfoFactory& rhs) = delete;
public:
	WorldInfoFactory();
	WorldInfoFactory(const std::string& name);
	virtual ~WorldInfoFactory();
};