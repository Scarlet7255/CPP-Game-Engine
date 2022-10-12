#include "Bullet.h"
#include "Sprite.h"
#include "BasicMovement.h"

Bullet::Bullet(Game* game, string bulletName, string name):GameObject(game,name) {
	mBulletName = bulletName;
	SetActive(false);
}

void Bullet::Awake() {
	BasicMovement* movement = new BasicMovement(this);
	movement->MovementSpeed = 400.f;
	movement->AngularSpeed = M_PI*2.25f;
	AddComponent(movement);

	Sprite* sprite = new Sprite(this);
	sprite->SetTexture(GetOwner()->GetTexture("../Chapter3/" + mBulletName));
	AddComponent(sprite);

	CircleCollider* collider = new CircleCollider(mTransform->position, 20.f, this);
	AddCollider(collider);
	mCollider = collider;
}

void Bullet::Enable(Eigen::Vector2f pos) {
	mTransform->position = pos;
	mTransform->rotation = 0.f;
	mlifeTime = 15.f;
	SetActive(true);
}

void Bullet::UpdateGameObject(float deltaTime) {
	mlifeTime -= deltaTime;
	if (mlifeTime <= 0.f) Destory();
	mCollider->Center = mTransform->position;
}