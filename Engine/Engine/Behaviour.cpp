#include "Behaviour.h"

Behaviour::Behaviour(GameObject* gameObject, int UpdateOrder) {
	mgameObject = gameObject;
	mUpdateOrder = UpdateOrder;
}

Behaviour::~Behaviour() {
}

void Behaviour::Update(float deltaTime) {
}

void Behaviour::ProcessInput(const uint8_t* keystate) {
}