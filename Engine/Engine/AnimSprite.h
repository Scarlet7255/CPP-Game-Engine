#pragma once
#ifndef ANIMSPRITE_H
#define ANIMSPRITE_H

#include "Sprite.h"
#include <SDL.h>

//shows boundry and continue time for each sprite animation
struct SpriteSlice
{
    SDL_Rect srcret;
    float totalFrames;
};
class AnimSprite :
    public Sprite
{
public:
    AnimSprite(class GameObject* owner, int drawOrder = 100);

    // we need to update sprite every frame
    void Update(float deltaTime) override;
    // void Draw
    void Draw(SDL_Renderer*) override;

    // get/set FPS
    float GetAnimFPS() const { return mFPS; };
    void SetAnimFPS(float fps) { mFPS = fps; };
    
    void SetAnimTextures(const std::vector<SpriteSlice> *textures) { mAnimTextures = *textures; };
    //if repeat, animation will loop when after the last sprite or it will keep the last sprite
    bool mRepeat = true;
    

private:
    //current FPS
    float mFPS;
    // frame now displayed
    float mCurrentFrame;

    //sprite animation informations
    std::vector<SpriteSlice> mAnimTextures;
    // current displayed Sprite Slice
    int mRectIdx = 0;
};

#endif // !ANIMSPRITE_H

