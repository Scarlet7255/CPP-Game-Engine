
#pragma once
#ifndef  GAMEOBJECT_H
#define GAMEOBJECT_H

#include<vector>
#include<string>
#include<unordered_map>
#include "Transform.h"
#include "Game.h"

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

		Game* GetOwner() const { return mOwner; };

		Transform* GetTransform() const { return mTransform; };

		string GetName() const { return mName; };

		void SetName(string name) { mName = name; };

		State GetState() const { return mState; };
		bool IsActive() const { return mState == EActive; };

		void SetActive(bool activeSelf) {
			if (mState == EDead) return;
			if (activeSelf) mState = EActive;
			else mState = EPause;
		}

		void Destory() {
			mState = EDead;
		}

		//update method called from game
		void Update(float deltaTime);
		//update all components attached to the game object
		void UpdateComponents(float deltaTime);
		//call when add the gameobject to the world
		virtual void Awake();
		//any specific update code
		virtual void UpdateGameObject(float deltaTime);
	
	protected:
		// transform informations
		Transform* const mTransform = new Transform();
		// components container
		vector<class Behaviour*> mComponents;
		string mName;
		Game* mOwner;

	private:
		// gameObject's state
		State mState;
	};
#endif // ! GAMEOBJECT_H