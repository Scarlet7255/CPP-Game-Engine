#pragma once
#ifndef  BEHAVIOUR_H
#define BEHAVIOUR_H
#include <SDL.h>
class Behaviour
{
public:
	// constructor and destructor
	Behaviour (class GameObject* gameObject, int updateOrder = 100);
	virtual ~Behaviour();
	int GetUpdateOrder() const { return mUpdateOrder; };
	virtual void Update(float deltaTime);
	virtual void ProcessInput(const uint8_t* keystate);
protected:
	int mUpdateOrder;
	class GameObject* mgameObject;
};

#endif // ! BEHAVIOUR_H