#include<vector>
#include<string>
#include "Transform.h"
#include "Game.h"
#pragma once
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
		GameObject(Game* game, string name);
		virtual ~GameObject();

		// add and remove gameobject
		void AddComponent(class Behaviour* behaviour);
		void AddComponents(vector<class Behaviour*> behaviours);
		void RemoveComponent(class Behaviour* behaviour);

		Transform* GetTransform() const { return mtransform; };

		string GetName() const { return mName; };

		void SetName(string name) { mName = name; };

		State GetState() const { return mState; };

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
		//any specific update code
		virtual void UpdateGameObject(float deltaTime);

	private:
		// gameObject's state
		State mState;
		// transform informations
		Transform* const mtransform = new Transform();
		// components container
		vector<class Behaviour*> mComponents;
		class Game* game;
		string mName;
	};

