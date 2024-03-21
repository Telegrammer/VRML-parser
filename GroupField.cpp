#include "GroupField.h"

GroupField::GroupField() : AbstractField(true, "untitled")
{
}

GroupField::GroupField(bool isExtern, const std::string& name) : AbstractField(isExtern, name)
{
}

GroupField::GroupField(bool isExtern, const std::string& name,const std::vector<AbstractField*>& data) : AbstractField(isExtern, name)
{
	_data.reserve(VECTOR_RESERVE_SIZE);
	for (int i = 0; i < data.size(); i++) {
		_data.push_back(data[i]->copy());
	}
}

GroupField::GroupField(bool isExtern, const std::string& name, std::vector<AbstractField*>&& tmpData) : AbstractField(isExtern, name) {
	_data.reserve(VECTOR_RESERVE_SIZE);
	for (int i = 0; i < tmpData.size(); i++) {
		_data.push_back(tmpData[i]);
		tmpData[i] = nullptr;
	}
}

GroupField::GroupField(const GroupField& rhs) : AbstractField(rhs)
{
	_data.reserve(VECTOR_RESERVE_SIZE);
	for (int i = 0; i < rhs._data.size(); i++) {
		_data.push_back(rhs._data[i]->copy());
	}
}

GroupField& GroupField::operator=(const GroupField& rhs)
{
	if (this != &rhs) {
		for (int i = 0; i < _data.size(); i++) {
			delete _data[i];
		}
		for (int i = 0; i < rhs._data.size(); i++) {
			_data.push_back(rhs._data[i]->copy());
		}
	}
	return *this;
}

GroupField::~GroupField()
{
	for (int i = 0; i < _data.size(); i++) {
		delete _data[i];
	}
}

GroupField* GroupField::copy()
{
	return new GroupField(*this);
}

std::vector<AbstractField*>& GroupField::getData()
{
	return _data;
}

void GroupField::setData(const std::vector<AbstractField*> other)
{
	for (int i = 0; i < _data.size(); i++) {
		delete _data[i];
	}
	for (int i = 0; i < other.size(); i++) {
		_data.push_back(other[i]->copy());
	}
}

void GroupField::addFieldPtr(AbstractField* field)
{
	_data.push_back(field);
}

void GroupField::setData(AbstractField* other) {}