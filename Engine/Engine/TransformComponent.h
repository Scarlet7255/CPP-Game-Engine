#include <Eigen/Core>
#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#pragma once
	class TransformComponent
	{
	public:
		Eigen::Vector2f scale{ 1.0f,1.0f };
		Eigen::Vector2f position{ 0.f,0.f };
		float rotation = 0.0f;
		void SetPosition(float x, float y) {
			position = Eigen::Vector2f(x, y);
		}

		void SetScale(float x, float y) {
			scale = Eigen::Vector2f(x, y);
		}
	};


#endif // !TRANSFORM_H



