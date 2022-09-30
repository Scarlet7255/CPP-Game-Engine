#pragma once
#ifndef SPRITE_H
#define SPRITE_H
#include "Behaviour.h"
#include "GameObject.h"
#include "SDL.h"
class Sprite :
    public Behaviour
{
public:
    Sprite(GameObject* owner, int drawOrder = 100);
    ~Sprite();

    virtual void Draw(SDL_Renderer*);
    virtual void SetTexture(SDL_Texture*);

    int GetDrawOrder() const { return mDrawOrder; };
    int GetTextureHeight() const { return mTexHeight; };
    int GetTextureWidtht() const { return mTexWidth; };
    
    Vector2 GetSpriteScale() const { return mSpriteScale; };
    void SetSpriteScale(Vector2 scale) { mSpriteScale = scale; };
    void SetSpriteOffset(Vector2 offset) { mSpriteOffset= offset; };
protected:
    // texture to draw
    SDL_Texture* mTexture;
    // draw order used for painter's algorithm
    int mDrawOrder;
    // Width/Height of texture
    int mTexWidth;
    int mTexHeight;
    Vector2 mSpriteScale{1.f,1.f};
    Vector2 mSpriteOffset{ 0.f,0.f };
};

#endif

