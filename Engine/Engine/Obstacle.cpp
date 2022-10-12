#include "Obstacle.h"
#include "BasicMovement.h"
#include "Sprite.h"
Obstacle::Obstacle(Game* game, string name):GameObject(game,name) {}

void Obstacle::Awake() {
	mTransform->SetPosition(500.f, 395.f);

	BasicMovement* movement = new BasicMovement(this);

	movement->MovementSpeed = 100.f;
	movement->AngularSpeed = 0.f;
	AddComponent(movement);

	mTransform->rotation = M_PI;

	Sprite *sprite = new Sprite(this);
	sprite->SetTexture(GetOwner()->GetTexture("../Chapter3/obstacle.png"));
	sprite->SetSpriteScale(Eigen::Vector2f(0.6f, -0.6f));
	AddComponent(sprite);

	mCollider = new CircleCollider(mTransform->position,30,this);
	AddCollider(mCollider);
}

void Obstacle::UpdateGameObject(float deltaTime) {
	if (mTransform->position[0] < -30.f) mTransform->position[0] = rand() % 200 + 600;
	if (GetOwner()->CollideDetect(mCollider)) mTransform->position[0] = rand() % 200 + 600;
	mCollider->Center = mTransform->position;
}