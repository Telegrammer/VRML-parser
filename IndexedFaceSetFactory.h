#pragma once

#include "IndexedLineSetFactory.h"
#include "NormalFactory.h"

class IndexedFaceSetFactory : public IndexedLineSetFactory {
private:
	virtual void initTokens();
	IndexedFaceSetFactory(const IndexedFaceSetFactory& rhs) = delete;
	IndexedLineSetFactory& operator=(const IndexedFaceSetFactory& rhs) = delete;
public:
	IndexedFaceSetFactory();
	IndexedFaceSetFactory(const std::string& name);
	virtual ~IndexedFaceSetFactory();
};