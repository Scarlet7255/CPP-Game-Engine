#pragma once
#ifndef BASICMOVEMENT_H
#define BASICMOVEMENT_H

#include "Behaviour.h"
class BasicMovement :
    public Behaviour
{
public:
    BasicMovement(GameObject* owner, int updateOrder = 10);
    void Update(float) override;

    float AngularSpeed = 0.f;
    float MovementSpeed = 0.f;
protected:
    class TransformComponent* mTransform;
};

#endif

