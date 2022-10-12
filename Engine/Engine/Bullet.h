#pragma once
#include "GameObject.h"
class Bullet :
    public GameObject
{

public:
    Bullet(Game*, string bulletName, string name = "bullet");
    virtual void Awake() override;
    virtual void UpdateGameObject(float deltaTime) override;
    virtual void Enable(Eigen::Vector2f pos);
    

protected:
    string mBulletName;
    float mlifeTime = 15.F;
    CircleCollider* mCollider;
};

