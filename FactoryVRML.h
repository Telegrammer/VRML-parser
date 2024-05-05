#pragma once

#include "AbstractFactory.h"
#include "TransformFactory.h"
#include "ShapeFactory.h"
#include "ViewpointFactory.h"
#include "WorldInfoFactory.h"
#include "BackgroundFactory.h"


class FactoryVRML : public AbstractFactory {
private:
	virtual void initTokens();
	FactoryVRML(const FactoryVRML& rhs) = delete;
	FactoryVRML& operator=(const FactoryVRML& rhs) = delete;
public:
	FactoryVRML();
	FactoryVRML(const std::string& name);
	virtual ~FactoryVRML();
	virtual GroupField* decrypt(bool isExtern, const std::string& fileData) override;
};