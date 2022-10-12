#include "Bullet2.h"
#include "BasicMovement.h"
#include "Sprite.h"

void Bullet2::Awake() {
	BasicMovement* movement = new BasicMovement(this);
	movement->MovementSpeed = 400.f;
	AddComponent(movement);
	Sprite* sprite = new Sprite(this);
	sprite->SetTexture(GetOwner()->GetTexture("../Chapter3/" + mBulletName));
	AddComponent(sprite);
	CircleCollider* collider = new CircleCollider(mTransform->position, 20.f, this);
	AddCollider(collider);
	mCollider = collider;
}

void Bullet2::Enable(Eigen::Vector2f pos) {
	mTransform->position = pos;
	mTransform->rotation = 0.f;
	mlifeTime = 1.f;
	SetActive(true);
}