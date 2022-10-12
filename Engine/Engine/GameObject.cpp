#include "GameObject.h"
#include "Game.h"
#include "Behaviour.h"
#include <string>
#include <algorithm>
using namespace std;

#pragma region Constructor And Destructor

GameObject::GameObject(Game* owner, string name) {
	mName = name;
	mOwner = owner;
}

GameObject::~GameObject() {
	delete mTransform;
	int size = mComponents.size();
	for (int i = 0; i < size; i++) {
		delete mComponents[i];
	}
}

void GameObject::Destory() {
	mState = EDead;
}
#pragma endregion

#pragma region Add and Remove Component
bool CompareComponent(class Behaviour* a, class Behaviour* b) {
	return a->GetUpdateOrder() < b->GetUpdateOrder();
}

void GameObject::AddComponent(Behaviour* component) {
	mComponents.push_back(component);
	sort(mComponents.begin(), mComponents.end());
}

void GameObject::AddComponents(vector<Behaviour*> container) {
	int size = container.size();
	for (int i = 0; i < size; i++) {
		mComponents.push_back(container[i]);
	}
	sort(mComponents.begin(), mComponents.end(), CompareComponent);
}

void GameObject::RemoveComponent(Behaviour* behaviour) {
	for (auto it = mComponents.begin(); it != mComponents.end(); it++) {
		if((* it) == behaviour)
		mComponents.erase(it);
		break;
	}
	delete behaviour;
};

void GameObject::AddCollider(CircleCollider* collider) {
	AddComponent(collider);
	GetOwner()->AddCollider(collider);
}
#pragma endregion

#pragma region Update 

void GameObject::Awake() {
};

void GameObject::Update(float deltaTime) {
	if(mState==EActive) UpdateComponents(deltaTime);
	UpdateGameObject(deltaTime);
}

void GameObject::UpdateComponents(float deltaTime) {
	for (auto it = mComponents.begin(); it != mComponents.end(); ++it) {
		(* it)->Update(deltaTime);
	}
}

void GameObject::UpdateGameObject(float deltaTime) {
}
#pragma endregion

#pragma region Process Input
void GameObject::ProcessInput(const uint8_t* keystate) {
	if (mState != EActive) return;
	for (auto it = mComponents.begin(); it != mComponents.end(); it++) {
		(*it)->ProcessInput(keystate);
	}
	ActorInput(keystate);
}

void GameObject::ActorInput(const uint8_t* keystate) {
}
#pragma endregion



