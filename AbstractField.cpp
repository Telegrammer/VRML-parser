#include "AbstractField.h"

AbstractField::AbstractField() : _isExtern(false), _name("none") {
}

AbstractField::AbstractField(bool isExtern, const std::string& name) : _isExtern(isExtern), _name(name) {
}

AbstractField::AbstractField(const AbstractField& rhs) : _isExtern(rhs._isExtern), _name(rhs._name) {
}

AbstractField& AbstractField::operator=(const AbstractField& rhs) {
	if (this != &rhs) {
		_isExtern = rhs._isExtern;
	}
	return *this;
}

AbstractField::AbstractField(AbstractField&& tmpRhs) noexcept : _isExtern(tmpRhs._isExtern), _name(tmpRhs._name)
{
}

AbstractField& AbstractField::operator=(AbstractField&& tmpRhs) noexcept
{
	if (this != &tmpRhs) {
		_isExtern = tmpRhs._isExtern;
		_name = tmpRhs._name;
	}
	return *this;
}

AbstractField::~AbstractField() {};
