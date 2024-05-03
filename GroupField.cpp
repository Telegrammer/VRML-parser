#include "GroupField.h"
#include <iostream>

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
	_data.clear();
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

std::set<std::string> GroupField::getNames()
{
	std::set<std::string> result;
	for (std::vector<AbstractField*>::const_iterator it = _data.begin(); it != _data.end(); it++) {
		result.insert((*it)->getName());
	}
	return result;
}

void GroupField::addFieldPtr(AbstractField* field)
{
	_data.push_back(field);
}

void GroupField::print(std::ostream& os, size_t& depth)
{
	os << std::string(depth, '\t');
	_isExtern == true ? os << "extern " : os << "";
	os << _name;
	if (_data.size() == 0) {
		os << " NULL\n";
		return;
	}
	os << " {\n";
	++depth;
	for (int i = 0; i < _data.size(); i++) {
		_data[i]->print(os, depth);
	}
	--depth;
	os << std::string(depth, '\t') + "}\n";
}

void GroupField::setData(AbstractField* other) {}
