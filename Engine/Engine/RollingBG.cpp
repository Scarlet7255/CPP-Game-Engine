#include "RollingBG.h"
RollingBG::RollingBG(GameObject* owner, int drawOrder):Sprite(owner,drawOrder) {}

void RollingBG::Update(float deltaTime) {
	mRollingDistance += mRollingSpeed * deltaTime;
	
	// means horizontal movement
	if (mDir > 1) {
		// moved to the mid, go back to origin
		if ( mRollingDistance >= mTexWidth / 2) {
			mRollingDistance = 0;
		}
		mRect.x = static_cast<int>(mDir == Right? mRollingDistance : mTexWidth/2-mRollingDistance);
	}
	else {
		if ( mRollingDistance >= mTexHeight / 2) {
			mRollingDistance = 0;
		}
		mRect.y = static_cast<int>(mDir == Down ? mRollingDistance : mTexHeight / 2 - mRollingDistance);
	}
}

void RollingBG::Draw(SDL_Renderer *renderer) {
	// if it got texture and the owner is active, it will draw
	if (!mTexture || !mgameObject->IsActive()) return;

	SDL_Rect r;

	Vector2 scale = mgameObject->GetTransform()->scale;
	//set sprite scale draw on the screen
	r.w = (int)(scale.x * mTexWidth * mSpriteScale.x);
	r.h = (int)(scale.y * mTexHeight * mSpriteScale.y);
	// set where sprite draw on the screen
	Vector2 pos = mgameObject->GetTransform()->position;
	r.x = (int)(pos.x - r.w / 2 + mSpriteOffset.x);
	r.y = (int)(pos.y - r.h / 2 + mSpriteOffset.y);

	float rotation = mgameObject->GetTransform()->rotation;
	SDL_RenderCopyEx(renderer,
		mTexture,
		&mRect,//null to draw whole texture
		&r,// where to draw
		-(rotation / M_PI) * 180.0, // convert radius to clockwise angle
		nullptr,//point of rotation, null for texture centure
		SDL_FLIP_NONE);// no filp
}

