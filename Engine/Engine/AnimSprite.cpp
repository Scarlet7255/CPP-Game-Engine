#include "AnimSprite.h"
#include <iostream>
AnimSprite::AnimSprite(GameObject* owner, int drawOrder):Sprite(owner,drawOrder) {
	mFPS = 30.f;
	mCurrentFrame = 0.f;
}

void AnimSprite::Update(float deltaTime)  {
	if (mAnimTextures.size() < 1) return;
	
	int size = mAnimTextures.size();
	// calculate the frame
	mCurrentFrame += mFPS*deltaTime;

	if (mCurrentFrame > mAnimTextures[mRectIdx].totalFrames) {
		mCurrentFrame =0.f;
		++mRectIdx;
		if (mRepeat)mRectIdx %= size;
		else mRectIdx = min(mRectIdx, size - 1);
		//else mRectIdx = size - 1;
	}

}

void AnimSprite::Draw(SDL_Renderer* renderer) {
	// if it got texture and the owner is active, it will draw
	if (!mTexture || !mgameObject->IsActive()) return;

	SDL_Rect r;

	Vector2 scale = mgameObject->GetTransform()->scale;
	//set sprite scale draw on the screen
	r.w = (int)(scale.x * mTexWidth * mSpriteScale.x);
	r.h = (int)(scale.y * mTexHeight * mSpriteScale.y);
	// set where sprite draw on the screen
	Vector2 pos = mgameObject->GetTransform()->position;
	r.x = (int)(pos.x - r.w /2);
	r.y = (int)(pos.y - r.h / 2);

	SDL_Rect* rec = mAnimTextures.size() < 1? nullptr: &mAnimTextures[mRectIdx].srcret;
	float rotation = mgameObject->GetTransform()->rotation;
	SDL_RenderCopyEx(renderer,
		mTexture,
		rec,//null to draw whole texture
		&r,// where to draw
		-(rotation/M_PI)*180.0, // convert radius to clockwise angle
		nullptr,//point of rotation, null for texture centure
		SDL_FLIP_NONE);// no filp
}