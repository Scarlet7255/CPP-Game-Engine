#pragma once
#ifndef  ANGLE_H
#define ANGLE_H
#include "GameObject.h"
#include "AnimSprite.h"
class Angle :
    public GameObject
{
public:
    Angle(Game*, string name = "angle");
    void Awake() override;
    void UpdateGameObject(float deltaTime) override;

private:
    vector<SpriteSlice> mSlices;
    CircleCollider* mCollider;
};

#endif // ! ANGLE_H

