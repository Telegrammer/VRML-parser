#pragma once



class Transform{
public:
	Transform();
	Transform(const Transform& rhs);
	Transform& operator=(const Transform& rhs);
	Transform(Transform&& tmpRhs);
	Transform& operator=(Transform&& tmpRhs);
	virtual Transform* copy();
	virtual ~Transform();
};