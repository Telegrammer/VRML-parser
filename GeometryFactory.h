#pragma once


#include "ConeFactory.h"

class GeometryFactory : public AbstractFactory {
private:
	virtual void initTokens();
	GeometryFactory(const GeometryFactory& rhs) = delete;
	GeometryFactory& operator=(const GeometryFactory& rhs) = delete;
public:
	GeometryFactory();
	GeometryFactory(const std::string& name);
	virtual ~GeometryFactory();
};