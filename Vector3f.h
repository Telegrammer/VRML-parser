#pragma once
#include <vector>
#include <ostream>

class Vector3f {

private:
	std::vector<float*> _data;

public:
	Vector3f();
	Vector3f(std::vector<float*>&& data);
	Vector3f(const std::vector<float*>& data);
	Vector3f(const Vector3f& rhs);
	Vector3f& operator=(const Vector3f& rhs);
	void push_back(const float value);
	friend std::ostream& operator<<(std::ostream& os, const Vector3f& vec);

	~Vector3f();
};