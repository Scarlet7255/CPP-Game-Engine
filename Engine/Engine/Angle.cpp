#include "Angle.h"
#include "BasicMovement.h"
Angle::Angle(Game* game, string name):GameObject(game,name) {
	mSlices.push_back(SpriteSlice{0,0,90,81,6.f});
	mSlices.push_back(SpriteSlice{ 90,0,90,81,6.f });
	mSlices.push_back(SpriteSlice{ 180,0,90,81,6.f });
	mSlices.push_back(SpriteSlice{ 270,0,90,81,6.f });
	mSlices.push_back(SpriteSlice{ 0,0,90,81,6.f });

	mTransform->SetPosition(600.f, 230.f);
	mTransform->SetScale(0.2f, -0.15f);
	mTransform->rotation = M_PI;
}

void Angle::Awake() {

	AnimSprite* animSprite = new AnimSprite(this);
	animSprite->SetAnimTextures(&mSlices);
	animSprite->SetTexture(GetOwner()->GetTexture("../chapter3/angle.png"));
	animSprite->SetSpriteScale(Eigen::Vector2f{ 1.f,1.f });
	AddComponent(animSprite);

	BasicMovement* movement = new BasicMovement(this);

	movement->MovementSpeed = 130.f;
	movement->AngularSpeed = 0.f;
	AddComponent(movement);

	CircleCollider* collider = new CircleCollider(mTransform->position, 20.f, this);
	AddCollider(collider);
	mCollider = collider;
}

void Angle::UpdateGameObject(float deltaTime) {
	if (mTransform->position[0] < -10.f) mTransform->position[0] = rand() % 200 + 600;
	if (GetOwner()->CollideDetect(mCollider)) {
		mTransform->position[0] = rand() % 200 + 600;
	}
	mCollider->Center = mTransform->position;
}