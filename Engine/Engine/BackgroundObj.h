#pragma once
#ifndef BACKGROUNDOBJ_H
#define BGCKGROUNDOBJ_H
#include "GameObject.h"
class BackgroundObj :
    public GameObject
{
public:
    BackgroundObj(Game* owner, string name = "background");
    void Awake() override;
private:
    void SetMainBackground();
    void SetSecBackground();
};
#endif

