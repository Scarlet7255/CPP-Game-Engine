#include "BackgroundObj.h"
#include "RollingBG.h"

BackgroundObj::BackgroundObj(Game * owner, string name):GameObject(owner,name) {
	mTransform->SetPosition(0.f, -0.f);
}

void BackgroundObj::Awake() {
	SetMainBackground();
	SetSecBackground();
}

void BackgroundObj::SetMainBackground() {
	RollingBG* bg = new RollingBG(this);
	bg->SetTexture(mOwner->GetTexture("../Chapter2/forestRepeat.png"));
	bg->SetRollingArea(0, 0, 512, 512);
	bg->SetRollingSpeed(30.f);
	bg->SetRollingDir(RollingBG::Right);
	bg->SetSpriteScale(Eigen::Vector2f{ 1.0f, 1.8f });
	bg->SetSpriteScale(Eigen::Vector2f{ 1.0f, 1.8f });
	bg->SetSpriteOffset(Eigen::Vector2f{ 0.f, 140.f });
	AddComponent(bg);
}

void BackgroundObj::SetSecBackground() {
	RollingBG* bg = new RollingBG(this, 11);
	bg->SetTexture(mOwner->GetTexture("../Chapter2/bg2.png"));
	bg->SetRollingArea(0, 0, 512, 512);
	bg->SetRollingSpeed(50.f);
	bg->SetRollingDir(RollingBG::Right);
	bg->SetSpriteScale(Eigen::Vector2f{ 1.0f, 1.0f });
	bg->SetSpriteOffset(Eigen::Vector2f{ 0.f, 250.f });
	AddComponent(bg);
}