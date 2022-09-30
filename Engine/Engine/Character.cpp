#include "Character.h"
Character::Character(Game *owner, string name):GameObject(owner,name) {
	
	SpriteSlice first{ {0,128,52,64},6.f };
	SpriteSlice sec{ {64,128,52,64},6.f };
	SpriteSlice thi{ {128,128,52,64},6.f };
	SpriteSlice sec2{ {64,128,52,64},6.f };

	mSlices.push_back(first);
	mSlices.push_back(sec);
	mSlices.push_back(thi);
	mSlices.push_back(sec2);

	mTransform->SetScale(1.f, 1.f);

}

void Character::Awake() {
	mTransform->SetPosition(100.f, 380.f);
	AnimSprite* character = new AnimSprite(this);
	AddComponent(character);
	character->SetTexture(GetOwner()->GetTexture(string("../Chapter2/Sprite.png")));
	character->SetSpriteScale(Vector2{ 0.4f,0.4f });
	character->SetAnimTextures(&mSlices);
	ground = 380.f;
}

void Character::UpdateGameObject(float deltaTime) {
	Vector2 pos = mTransform->position;
	pos.y -= speed;
	mTransform->SetPosition(pos.x, pos.y);
	if (pos.y < ground) {
		speed -= 9.8f * deltaTime;
	}
	else {
		speed = 0.f;
		pos.y = ground;
	}
	
	const Uint8* state = SDL_GetKeyboardState(NULL);
	
	if (pos.y >= ground && state[SDL_SCANCODE_SPACE]) {
		speed = 5.f;
		SDL_Log("space");
	}
}