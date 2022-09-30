#include "Sprite.h"
#include "SDL_Image.h"
#include "GameObject.h"

Sprite::Sprite(GameObject* owner, int drawOreder):Behaviour(owner) {
	mgameObject = owner;
	mDrawOrder = drawOreder;
}

Sprite::~Sprite() {
	
}

void Sprite::SetTexture(SDL_Texture* tex) {
	mgameObject->GetOwner()->AddSprite(this);
	mTexture = tex;
	SDL_QueryTexture(tex, nullptr, nullptr, &mTexWidth, &mTexHeight);
}

void Sprite::Draw(SDL_Renderer* renderer) {
	// if it got texture and the owner is active, it will draw
	if (!mTexture || !mgameObject->IsActive()) return;

	SDL_Rect r;

	Vector2 scale = mgameObject->GetTransform()->scale;
	//set sprite scale draw on the screen
	r.w = (int)(scale.x*mTexWidth*mSpriteScale.x);
	r.h = (int)(scale.y * mTexHeight*mSpriteScale.y);
	// set where sprite draw on the screen
	Vector2 pos = mgameObject->GetTransform()->position;
	r.x = (int)(pos.x - r.w /2 + mSpriteOffset.x);
	r.y = (int)(pos.y - r.h / 2 + mSpriteOffset.y);

	float rotation = mgameObject->GetTransform()->rotation;
	SDL_RenderCopyEx(renderer,
		mTexture,
		nullptr,//null to draw whole texture
		&r,// where to draw
		-(rotation/M_PI)*180.0, // convert radius to clockwise angle
		nullptr,//point of rotation, null for texture centure
		SDL_FLIP_NONE);// no filp
}