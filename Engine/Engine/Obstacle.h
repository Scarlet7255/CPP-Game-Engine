#pragma once
#include "GameObject.h"
class Obstacle :
    public GameObject
{
public:
    Obstacle(class Game*, string name = "Obstacle");
    void Awake() override;
    void UpdateGameObject(float deltaTime) override;

private:
    CircleCollider* mCollider;
};

