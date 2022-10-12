#pragma once
#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H
#include "Behaviour.h"
#include "Game.h"
class CircleCollider :
    public Behaviour
{
public:
    /// <summary>
    /// define circle collider with radius and center
    /// </summary>
    /// <param name="pos">:the center of the collider</param>
    CircleCollider(Eigen::Vector2f pos, float radius, GameObject* owner, int updateOrder = 100);
    ~CircleCollider();

    float Radius;
    Eigen::Vector2f Center;
};


#endif // !CIRCLECOLLIDER_H


