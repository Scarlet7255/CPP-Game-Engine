#include "Character.h"
#include "Bullet2.h"
Character::Character(Game *owner, string name):GameObject(owner,name) {
	
	SpriteSlice first{ {0,128,52,64},6.f };
	SpriteSlice sec{ {64,128,52,64},6.f };
	SpriteSlice thi{ {128,128,52,64},6.f };

	mSlices.push_back(first);
	mSlices.push_back(sec);
	mSlices.push_back(thi);
	mSlices.push_back(sec);

	mTransform->SetScale(1.f, 1.f);

}

void Character::Awake() {
	mTransform->SetPosition(100.f, 380.f);
	AnimSprite* character = new AnimSprite(this);
	AddComponent(character);
	character->SetTexture(GetOwner()->GetTexture(string("../Chapter2/Sprite.png")));
	character->SetSpriteScale(Eigen::Vector2f{ 0.4f,0.4f });
	character->SetAnimTextures(&mSlices);
	ground = 380.f;

	mcollider = new CircleCollider(mTransform->position, 20.f,this);
	AddCollider(mcollider);
}

void Character::ActorInput(const uint8_t* keystate) {
	Eigen::Vector2f pos = mTransform->position;
	if (pos[1] >= ground && keystate[SDL_SCANCODE_SPACE]) {
		speed = 6.4f;
	}
	if (keystate[SDL_SCANCODE_K] && coldK<0.f) {
		Bullet* ammo = new Bullet(GetOwner(), "1.png");
		GetOwner()->AddGameObject(ammo);
		ammo->Enable(mTransform->position + Eigen::Vector2f(0.f,-55.f));
		coldK = 5.f;
	}
	if (keystate[SDL_SCANCODE_J] && coldJ < 0.f) {
		Bullet2* ammo = new Bullet2(GetOwner(), "2.png");
		GetOwner()->AddGameObject(ammo);
		ammo->Enable(mTransform->position + Eigen::Vector2f(0.f, -15.f));
		coldJ = 1.f;
	}
}

void Character::UpdateGameObject(float deltaTime) {
	Eigen::Vector2f pos = mTransform->position;
	pos[1] -= speed;
	mTransform->SetPosition(pos[0], pos[1]);
	if (pos[1] < ground) {
		speed -= 9.8f * deltaTime;
	}
	else {
		speed = 0.f;
		pos[1] = ground;
	}
	if (coldK >= 0.f) coldK -= deltaTime;
	if (coldJ >= 0.f) coldJ -= deltaTime;

	mcollider->Center = mTransform->position;
}