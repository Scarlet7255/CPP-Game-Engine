#pragma once
#include "GameObject.h"
#include "AnimSprite.h"
class Character :
    public GameObject
{
public:
    Character(class  Game*, string name = "Character");
    void Awake() override;
    void UpdateGameObject(float) override;

private:
   vector<SpriteSlice> mSlices;
   float speed = 0.f;
   float ground = 0.f;
};

