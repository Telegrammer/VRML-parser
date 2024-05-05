#include "Vector3f.h"

Vector3f::Vector3f()
{
	_data.reserve(3);
}

Vector3f::Vector3f(std::vector<float*>&& data)
{
	_data.reserve(3);
	for (int i = 0; i < data.size(); i++) {
		_data.push_back(data[i]);
		data[i] = nullptr;
	}
}

Vector3f::Vector3f(const std::vector<float*>& data)
{
	_data.reserve(3);
	for (int i = 0; i < data.size(); i++) {
		_data.push_back(new float(*data[i]));
	}
}

Vector3f::Vector3f(const Vector3f& rhs)
{
	_data.reserve(3);
	for (int i = 0; i < rhs._data.size(); i++) {
		_data.push_back(new float(*rhs._data[i]));
	}
}

Vector3f& Vector3f::operator=(const Vector3f& rhs)
{
	if (this != &rhs) {
		for (int i = 0; i < _data.size(); i++) {
			delete _data[i];
		}
		for (int i = 0; i < rhs._data.size(); i++) {
			_data.push_back(new float(*rhs._data[i]));
		}
	}
	return *this;
}

void Vector3f::push_back(const float value)
{
	if (_data.size() < 3) {
		_data.push_back(new float(value));
	}
}

Vector3f::~Vector3f()
{
	for (int i = 0; i < _data.size(); i++) {
		delete _data[i];
	}
}

std::ostream& operator<<(std::ostream& os, const Vector3f& vec)
{
	if (vec._data.size() != 0) {
		os << *vec._data[0] << " " << *vec._data[1] << " " << *vec._data[2];
	}
	return os;
}
