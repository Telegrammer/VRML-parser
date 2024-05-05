#pragma once

#include "AbstractFactory.h"
#include "CoordinateFactory.h"

class IndexedLineSetFactory : public AbstractFactory {
private:
	virtual void initTokens();
	IndexedLineSetFactory(const IndexedLineSetFactory& rhs) = delete;
	IndexedLineSetFactory& operator=(const IndexedLineSetFactory& rhs) = delete;
public:
	IndexedLineSetFactory();
	IndexedLineSetFactory(const std::string& name);
	virtual ~IndexedLineSetFactory();
};