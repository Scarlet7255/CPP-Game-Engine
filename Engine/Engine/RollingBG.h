#pragma once
#ifndef ROLLINGBG_H
#define ROLLINGBG_H

#include "Sprite.h"

class RollingBG :
    public Sprite
{
public:
    enum RollingDir{
        Up = 0, Down = 1, Left = 2, Right = 3
    };

    RollingBG(class  GameObject* owner, int drawOrder = 10);
    void Update(float) override;
    void Draw(SDL_Renderer*) override;

    // the area of background first draw on the screen
    void SetRollingArea(int x, int y, int w, int h) {
        mOrigin = { x,y,w,h }; 
        mRect = mOrigin; 
        mRollingDistance = mOrigin.x;
    };

    // set the direction we roll the background
    void SetRollingDir(RollingDir dir = Right) { mDir = dir; }
    void SetRollingSpeed(float speed) { mRollingSpeed = speed; }

private:
    // the area of background first draw on the screen
    SDL_Rect mOrigin{ 0,0,0,0 };
    // the real rect we draw on the screen
    SDL_Rect mRect;
    // direction of rolling
    RollingDir mDir = Right;
    float mRollingSpeed = 0.f;
    //record how far background rolling
    float mRollingDistance = 0.f;
};

#endif


