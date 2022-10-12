
#pragma once
#ifndef  GAMEOBJECT_H
#define GAMEOBJECT_H

#include<vector>
#include<string>
#include<unordered_map>
#include "TransformComponent.h"
#include "Game.h"
#include "CircleCollider.h"

using namespace std;
	class GameObject
	{
	public:

		// track state of gameobject
		enum State{
			EActive,
			EPause,
			EDead
		};

		// constructor and destructor
		GameObject(class  Game* , string name);
		virtual ~GameObject();

		// add and remove gameobject
		void AddComponent(class Behaviour* behaviour);
		void AddComponents(vector<class Behaviour*> behaviours);
		void RemoveComponent(class Behaviour* behaviour);
		void AddCollider(class CircleCollider* collider);

#pragma region getter and setter
		Game* GetOwner() const { return mOwner; };
		TransformComponent* GetTransform() const { return mTransform; };
		string GetName() const { return mName; };
		void SetName(string name) { mName = name; };
		bool IsDead() const { return mState == EDead; };
		bool IsActive() const { return mState == EActive; };
		void SetActive(bool activeSelf) {
			if (mState == EDead) return;
			if (activeSelf) mState = EActive;
			else mState = EPause;
		}
		Eigen::Vector2f GetForwardBase() { return Eigen::Vector2f(cosf(mTransform->rotation), sinf(mTransform->rotation)); };
		string GetName() { return mName; };
#pragma endregion

		//update method called from game
		void Update(float deltaTime);

		//update all components attached to the game object
		void UpdateComponents(float deltaTime);

		//call when add the gameobject to the world
		virtual void Awake();

		//any specific update code
		virtual void UpdateGameObject(float deltaTime);

		//process input for all components and gameobject self
		void ProcessInput(const uint8_t* keystate);
		virtual void ActorInput(const uint8_t* keystate);

		// destory gameobject in next frame
		void Destory();
	
	protected:
		// TransformComponent informations
		TransformComponent* const mTransform = new TransformComponent();
		// components container
		vector<class Behaviour*> mComponents;
		string mName;
		Game* mOwner;

	private:
		// gameObject's state
		State mState;
	};
#endif // ! GAMEOBJECT_H