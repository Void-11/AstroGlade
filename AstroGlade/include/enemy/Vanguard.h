﻿#pragma once
#include "Enemy/EnemySpaceship.h"

namespace ly
{
    class LaserShooter;
    class Vanguard : public EnemySpaceship
    {
    public:
        
        Vanguard(World* owningWorld, const std::string& texturePath = "PNG/Enemies/enemyBlue3.png", const sf::Vector2f& velocity = {0.f, 150.f});
        virtual void Tick(float deltaTime) override;
    private:
        
        virtual void Shoot() override;
        unique<LaserShooter> mShooter;
    };
}
