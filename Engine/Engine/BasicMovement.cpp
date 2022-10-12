#include "BasicMovement.h"
#include "GameObject.h"

BasicMovement::BasicMovement(GameObject* owner, int updateOrder):Behaviour(owner,updateOrder) {
	mTransform = owner->GetTransform();
};

void BasicMovement::Update(float deltaTime) {
	Eigen::Vector2f position = mTransform->position;
	float rotation = mTransform->rotation;

	position += mgameObject->GetForwardBase() * MovementSpeed * deltaTime;
	rotation += AngularSpeed * deltaTime;

	mTransform->position = position;
	mTransform->rotation = rotation;
}