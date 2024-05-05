#pragma once

#include "AbstractField.h"
#include <string>
#include <vector>
#include <type_traits>

template <typename T>
class Field : public AbstractField {
private:
	T* _data;
public:
	Field(bool isExtern, const std::string& name, const T& data);
	Field(const Field<T>& rhs);
	Field<T>& operator=(const Field<T>& rhs);
	Field(Field<T>&& tmpRhs);
	Field<T>& operator=(Field<T>&& tmpRhs);
	virtual ~Field();
	virtual Field* copy();
	virtual T& getData();
	virtual void setData(const T& other);
	virtual void print(std::ostream& os, size_t& depth);
};

template <typename U>
class Field<std::vector<U*>> : public AbstractField{
private:
	std::vector<U*> _data;
public:
	Field(bool isExtern, const std::string& name, const std::vector<U*>& data);
	Field(bool isExtern, const std::string& name, std::vector<U*>&& tmpData);
	Field(const Field<std::vector<U*>>& rhs);
	Field<std::vector<U*>>& operator=(const Field<std::vector<U*>>& rhs);
	Field(Field<std::vector<U*>>&& tmpRhs);
	Field<std::vector<U*>>& operator=(Field<std::vector<U*>>&& tmpRhs);
	virtual ~Field();
	virtual Field<std::vector<U*>>* copy();
	virtual std::vector<U*>& getData();
	virtual void setData(const std::vector<U*>& other);
	virtual void setData(const U& other, const std::size_t& index);
	virtual void print(std::ostream& os, size_t& depth);
};

/////////////////////////////////////

template<typename T>
inline Field<T>::Field(bool isExtern, const std::string& name, const T& data) : AbstractField(isExtern, name), _data(new T(data)) {
}


template<typename T>
inline Field<T>::Field(const Field<T>& rhs) : AbstractField(rhs), _data(new T(*rhs._data)) {
}

template<typename T>
inline Field<T>& Field<T>::operator=(const Field<T>& rhs) {
	if (this != &rhs) {
		delete _data;
		_data = new T(*(rhs._data));
	}
	return *this;
}

template<typename T>
inline Field<T>::Field(Field<T>&& tmpRhs) : AbstractField(tmpRhs), _data(new T())
{
	_data = tmpRhs._data;
	tmpRhs._data = nullptr;
}

template<typename T>
inline Field<T>& Field<T>::operator=(Field<T>&& tmpRhs)
{
	if (this != &tmpRhs) {
		delete _data;
		_data = tmpRhs._data;
		tmpRhs._data = nullptr;
	}
	return *this;
}

template<typename T>
inline Field<T>::~Field() {
	delete _data;
}

template<typename T>
inline Field<T>* Field<T>::copy() {
	return new Field<T>(*this);
}

template<typename T>
inline T& Field<T>::getData() {
	return *_data;
}

template<typename T>
inline void Field<T>::setData(const T& other) {
	*_data = other;
}

template<typename T>
inline void Field<T>::print(std::ostream& os, size_t& depth)
{
	os << std::string(depth, '\t');
	_isExtern == true ? os << "extern " : os << "";
	os << _name << " ";
	if (std::is_same<T, bool>::value) {
		os << (_data != nullptr ? "TRUE" : "FALSE");
	}
	else {
		os << *_data;
	}

	os << "\n";
}

////////////////////////////////////////

template<typename U>
inline Field<std::vector<U*>>::Field(bool isExtern, const std::string& name, const std::vector<U*>& data) : AbstractField(isExtern, name) {
	_data.reserve(data.size() + VECTOR_RESERVE_SIZE);
	for (int i = 0; i < data.size(); i++) {
		_data.push_back(new U(*data[i]));
	}
}

template<typename U>
inline Field<std::vector<U*>>::Field(bool isExtern, const std::string& name, std::vector<U*>&& tmpData) : AbstractField(isExtern, name) {
	_data.reserve(tmpData.size() + VECTOR_RESERVE_SIZE);
	for (int i = 0; i < tmpData.size(); i++) {
		_data.push_back(tmpData[i]);
		tmpData[i] = nullptr;
	}
	return;
}

template<typename U>
inline Field<std::vector<U*>>::Field(const Field<std::vector<U*>>& rhs) : AbstractField(rhs) {
	_data.reserve(rhs._data.size() + VECTOR_RESERVE_SIZE);
	for (int i = 0; i < rhs._data.size(); i++) {
		_data.push_back(new U(*(rhs._data[i])));
	}
}

template<typename U>
inline Field<std::vector<U*>>& Field<std::vector<U*>>::operator=(const Field<std::vector<U*>>& rhs) {
	if (this != &rhs) {
		for (int i = 0; i < _data.size(); i++) {
			delete _data[i];
		}
		for (int i = 0; i < rhs._data.size(); i++) {
			_data.push_back(new U(*(rhs._data[i])));
		}
	}
	return *this;
}

template<typename U>
inline Field<std::vector<U*>>::Field(Field<std::vector<U*>>&& tmpRhs) {
	_data.reserve(tmpRhs._data.size() + VECTOR_RESERVE_SIZE);
	for (int i = 0; i < tmpRhs._data.size(); i++) {
		_data.push_back(tmpRhs._data[i]);
		tmpRhs._data[i] = nullptr;
	}
}

template<typename U>
inline Field<std::vector<U*>>& Field<std::vector<U*>>::operator=(Field<std::vector<U*>>&& tmpRhs) {
	if (this != &tmpRhs) {
		for (int i = 0; i < _data.size(); i++) {
			delete _data[i];
		}
		for (int i = 0; i < tmpRhs._data.size(); i++) {
			_data.push_back(tmpRhs._data[i]);
			tmpRhs._data[i] = nullptr;
		}
	}
	return *this;
}
template<typename U>
inline Field<std::vector<U*>>::~Field() {
	for (int i = 0; i < _data.size(); i++) {
		delete _data[i];
	}
}

template<typename U>
inline Field<std::vector<U*>>* Field<std::vector<U*>>::copy() {
	return new Field<std::vector<U*>>(*this);
}

template<typename U>
inline std::vector<U*>& Field<std::vector<U*>>::getData()
{
	return _data;
}

template<typename U>
inline void Field<std::vector<U*>>::setData(const std::vector<U*>& other) {
	for (int i = 0; i < _data.size(); i++) {
		delete _data[i];
	}
	for (int i = 0; i < other.size(); i++) {
		_data.push_back(new U(*other[i]));
	}
}

template<typename U>
inline void Field<std::vector<U*>>::setData(const U& other, const std::size_t& index) {
	delete _data[index];
	_data[index] = new U(other);
}

template<typename U>
inline void Field<std::vector<U*>>::print(std::ostream& os, size_t& depth)
{
	os << std::string(depth, '\t');
	_isExtern == true ? os << "extern " : os << "";
	os << _name << " [ ";
	std::string delimeter = _data.size() > VECTOR_RESERVE_SIZE ? ",\n" + std::string(depth, '\t') : ", ";
	
	if (_data.size() == 0) {
		os << " ]\n";
		return;
	}

	for (int i = 0; i < _data.size() - 1; i++) {
		os << *_data[i] << delimeter;
		switch (i%4)
		{
		case 3:
			delimeter = ",\n" + std::string(depth, '\t');
			break;
		default:
			delimeter = ", ";
			break;
		}
	}
	os << **(--_data.end());
	os << " ]\n";
}

///////////////////////////////////