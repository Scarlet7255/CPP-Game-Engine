#include "CircleCollider.h"
CircleCollider::CircleCollider(Eigen::Vector2f pos, float radius, GameObject* owner, int updateOrder):Behaviour(owner,updateOrder) {
	Center = pos;
	Radius = radius;
}

CircleCollider::~CircleCollider() {
	mgameObject->GetOwner()->RemoveCollider(this);
}

