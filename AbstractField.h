#pragma once
#include <string>
#include <ostream>
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
	virtual void print(std::ostream& os, size_t& depth) = 0;
	std::string& getName();
};