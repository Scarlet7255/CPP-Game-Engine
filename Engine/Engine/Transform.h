#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "Vector.h"
#pragma once

class Transform
{
public:
	Vector2 scale{ 1.0f,1.0f };
	Vector2 position{ 0.f,0.f };
	float rotation = 0.0f;

	void SetPosition(float x, float y) {
		position.x = x;
		position.y = y;
	}

	void SetScale(float x, float y) {
		scale.x = x;
		scale.y = y;
	}
};

#endif // !TRANSFORM_H



