#pragma once
#include "AbstractField.h"
#include <string>
#include <vector>

class GroupField : public AbstractField {
private:
	std::vector<AbstractField*> _data;
	void setData(AbstractField* other);
public:
	GroupField();
	GroupField(bool isExtern, const std::string& name);
	GroupField(bool isExtern, const std::string& name, const std::vector<AbstractField*>& data);
	GroupField(bool isExtern, const std::string& name, std::vector<AbstractField*>&& tmpData);
	GroupField(const GroupField& rhs);
	GroupField& operator=(const GroupField& rhs);
	virtual ~GroupField();
	virtual GroupField* copy();
	virtual std::vector<AbstractField*>& getData();
	virtual void setData(const std::vector<AbstractField*> other);
	void addFieldPtr(AbstractField* field);
};