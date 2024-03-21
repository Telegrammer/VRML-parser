#pragma once
#include <string>
#define VECTOR_RESERVE_SIZE 32

class AbstractField {
protected:
	bool _isExtern;
	std::string _name;
	AbstractField();
	AbstractField(bool isExtern, const std::string& name);
	AbstractField(const AbstractField& rhs);
	AbstractField& operator=(const AbstractField& rhs);
	AbstractField(AbstractField&& tmpRhs) noexcept;
	AbstractField& operator=(AbstractField&& tmpRhs) noexcept;
public:
	virtual ~AbstractField() = 0;
	virtual AbstractField* copy() = 0;

};