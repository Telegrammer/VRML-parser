#pragma once


#include "AbstractFactory.h"

class ViewpointFactory : public AbstractFactory {
private:
	virtual void initTokens();
	ViewpointFactory(const ViewpointFactory& rhs) = delete;
	ViewpointFactory& operator=(const ViewpointFactory& rhs) = delete;
public:
	ViewpointFactory();
	ViewpointFactory(const std::string& name);
	virtual ~ViewpointFactory();
};