#pragma once
class Behaviour
{
public:
	// constructor and destructor
	Behaviour(class GameObject* gameObject, int updateOrder = 100);
	virtual ~Behaviour();
	int GetUpdateOrder() const { return mUpdateOrder; };
	virtual void Update(float deltaTime);
private:
	int mUpdateOrder;
	class GameObject* mgameObject;
};

