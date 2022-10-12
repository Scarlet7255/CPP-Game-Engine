#pragma once
#include "Bullet.h"
class Bullet2 :
    public Bullet
{
public:
    Bullet2(Game* owner, string bulletName, string name = "bullet2"):Bullet(owner,bulletName,name) {};
    void Awake() override;
    void Enable(Eigen::Vector2f pos) override;
};

