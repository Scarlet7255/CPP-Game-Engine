#pragma once
#include "GameObject.h"
#include "AnimSprite.h"
#include "Bullet.h"
class Character :
    public GameObject
{
public:
    Character(class  Game*, string name = "Character");
    void Awake() override;
    void ActorInput(const uint8_t* keystate) override;
    void UpdateGameObject(float) override;

private:
   vector<SpriteSlice> mSlices;
   float speed = 0.f;
   float ground = 0.f;
   // sklll gap
   float coldK = -1.f;
   float coldJ = -1.f;
   CircleCollider* mcollider;
};

