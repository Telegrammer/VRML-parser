#pragma once


#include "AppearanceFactory.h"
#include "ConeFactory.h"
#include "BoxFactory.h"
#include "SphereFactory.h"
#include "CylinderFactory.h"

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