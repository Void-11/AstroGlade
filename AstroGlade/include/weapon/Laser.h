﻿#pragma once
#include "framework/Actor.h"

namespace ly
{
    class Laser : public Actor
    {
    public:

        Laser(World* world, Actor* owner, const std::string& texturePath, float speed = -1000.f, float damage = 10.f);

        void SetSpeed(float newSpeed);
        void SetDamage(float newDamage);

        virtual void Tick(float deltaTime) override;

    private:

        Actor* mOwner;
        float mSpeed;
        float mDamage;

        void Move(float deltaTime);
    };
}